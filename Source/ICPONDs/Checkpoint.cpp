#include "Checkpoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

ACheckpoint::ACheckpoint()
{
    PrimaryActorTick.bCanEverTick = true;

    // === ROOT COMPONENT ===
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // === TRIGGER SPHERE ===
    TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
    TriggerSphere->SetupAttachment(RootComponent);
    TriggerSphere->SetSphereRadius(TriggerRadius);
    TriggerSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TriggerSphere->SetGenerateOverlapEvents(true);

    // === CHECKPOINT MESH ===
    CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
    CheckpointMesh->SetupAttachment(RootComponent);
    CheckpointMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CheckpointMesh->SetGenerateOverlapEvents(false);

    // Try to load a basic checkpoint mesh (ring/torus shape)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CheckpointMeshObj(TEXT("/Engine/BasicShapes/Cylinder"));
    if (CheckpointMeshObj.Succeeded())
    {
        CheckpointMesh->SetStaticMesh(CheckpointMeshObj.Object);
        // Scale to make it look like a checkpoint ring
        CheckpointMesh->SetWorldScale3D(FVector(3.f, 3.f, 0.2f));
    }

    // === PARTICLE EFFECTS ===
    ParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleEffect"));
    ParticleEffect->SetupAttachment(CheckpointMesh);
    ParticleEffect->bAutoActivate = false;

    // Try to load particle effect
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleFX(TEXT("/Engine/VFX/P_Steam_Lit"));
    if (ParticleFX.Succeeded())
    {
        ParticleEffect->SetTemplate(ParticleFX.Object);
    }

    // === AUDIO COMPONENT ===
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(CheckpointMesh);
    AudioComponent->bAutoActivate = false;

    // Try to load checkpoint sound
    static ConstructorHelpers::FObjectFinder<USoundCue> CheckpointSoundCue(TEXT("/Engine/EditorSounds/Notifications/CompileSuccess_Cue"));
    if (CheckpointSoundCue.Succeeded())
    {
        AudioComponent->SetSound(CheckpointSoundCue.Object);
        AudioComponent->SetVolumeMultiplier(0.7f);
    }

    // === BIND OVERLAP EVENTS ===
    TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnTriggerBeginOverlap);
    TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &ACheckpoint::OnTriggerEndOverlap);

    // === INITIALIZE DEFAULT VALUES ===
    CheckpointState = ECheckpointState::Inactive;
    CheckpointType = ECheckpointType::Standard;
    bIsOptional = false;
    BonusPoints = 100.f;
    BonusTime = 0.f;

    // Set default valid trigger classes (can be customized)
    ValidTriggerClasses.Add(APawn::StaticClass());
}

void ACheckpoint::BeginPlay()
{
    Super::BeginPlay();
    
    TimeCreated = GetWorld()->GetTimeSeconds();
    
    // Update initial visual state
    UpdateVisualState();
    
    // Update trigger radius if changed
    TriggerSphere->SetSphereRadius(TriggerRadius);
    
    UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint '%s' (ID: %d) initialized as %s"), 
        *CheckpointName, CheckpointID, 
        CheckpointState == ECheckpointState::Active ? TEXT("ACTIVE") : TEXT("INACTIVE"));
}

void ACheckpoint::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update visual effects based on state
    UpdateVisualState();
    UpdateParticleEffects();
    
    // Draw debug visuals
    if (bShowDebugInfo || bShowDebugSphere)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FVector Location = GetActorLocation();
            
            // Draw trigger sphere
            if (bShowDebugSphere)
            {
                FColor DebugColor;
                switch (CheckpointState)
                {
                    case ECheckpointState::Inactive:
                        DebugColor = FColor::Silver;
                        break;
                    case ECheckpointState::Active:
                        DebugColor = FColor::Green;
                        break;
                    case ECheckpointState::Completed:
                        DebugColor = FColor::Blue;
                        break;
                }
                
                DrawDebugSphere(World, Location, TriggerRadius, 16, DebugColor, false, -1.f, 0, 2.f);
            }
            
            // Draw checkpoint info text
            if (bShowDebugInfo)
            {
                FString DebugText = FString::Printf(TEXT("%s\nID: %d\nState: %s\nPoints: %.0f"),
                    *CheckpointName,
                    CheckpointID,
                    CheckpointState == ECheckpointState::Active ? TEXT("ACTIVE") :
                    CheckpointState == ECheckpointState::Completed ? TEXT("DONE") : TEXT("WAITING"),
                    BonusPoints);
                
                DrawDebugString(World, Location + FVector(0, 0, 100), DebugText, 
                    nullptr, FColor::White, 0.f, true, 1.2f);
            }
        }
    }
}

// === PUBLIC FUNCTIONS ===

void ACheckpoint::ActivateCheckpoint()
{
    if (CheckpointState != ECheckpointState::Active)
    {
        CheckpointState = ECheckpointState::Active;
        UpdateVisualState();
        
        if (ParticleEffect)
        {
            ParticleEffect->Activate();
        }
        
        UE_LOG(LogTemp, Warning, TEXT("? Checkpoint '%s' ACTIVATED"), *CheckpointName);
    }
}

void ACheckpoint::DeactivateCheckpoint()
{
    if (CheckpointState != ECheckpointState::Inactive)
    {
        CheckpointState = ECheckpointState::Inactive;
        UpdateVisualState();
        
        if (ParticleEffect)
        {
            ParticleEffect->Deactivate();
        }
        
        UE_LOG(LogTemp, Log, TEXT("? Checkpoint '%s' DEACTIVATED"), *CheckpointName);
    }
}

void ACheckpoint::CompleteCheckpoint(AActor* TriggeringActor, float CompletionTime)
{
    if (CheckpointState == ECheckpointState::Active)
    {
        CheckpointState = ECheckpointState::Completed;
        UpdateVisualState();
        PlayTriggerEffects();

        // Broadcast the event
        OnCheckpointTriggered.Broadcast(this, TriggeringActor, CompletionTime);

        UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint '%s' COMPLETED by %s (Time: %.2f)"), 
            *CheckpointName, 
            TriggeringActor ? *TriggeringActor->GetName() : TEXT("Unknown"), 
            CompletionTime);

        // Show on-screen feedback
        if (GEngine)
        {
            FString CompletionMessage;
            switch (CheckpointType)
            {
                case ECheckpointType::Start:
                    CompletionMessage = FString::Printf(TEXT("?? START LINE CROSSED!"));
                    break;
                case ECheckpointType::Finish:
                    CompletionMessage = FString::Printf(TEXT("?? FINISH LINE! Time: %.2f"), CompletionTime);
                    break;
                case ECheckpointType::Bonus:
                    CompletionMessage = FString::Printf(TEXT("? BONUS CHECKPOINT! +%.0f points"), BonusPoints);
                    break;
                case ECheckpointType::TimeBonus:
                    CompletionMessage = FString::Printf(TEXT("? TIME BONUS! +%.1f seconds"), BonusTime);
                    break;
                default:
                    CompletionMessage = FString::Printf(TEXT("?? Checkpoint %d Complete!"), CheckpointID);
                    break;
            }
            
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, CompletionMessage);
        }
    }
}

void ACheckpoint::ResetCheckpoint()
{
    CheckpointState = ECheckpointState::Inactive;
    bActorInTrigger = false;
    CurrentTriggeringActor = nullptr;
    UpdateVisualState();
    
    if (ParticleEffect)
    {
        ParticleEffect->Deactivate();
    }
    
    UE_LOG(LogTemp, Log, TEXT("?? Checkpoint '%s' RESET"), *CheckpointName);
}

bool ACheckpoint::CanTrigger(AActor* Actor) const
{
    if (!Actor || CheckpointState != ECheckpointState::Active)
    {
        return false;
    }

    // Check if actor class is in valid trigger classes
    if (ValidTriggerClasses.Num() > 0)
    {
        bool bValidClass = false;
        for (const TSubclassOf<AActor>& ValidClass : ValidTriggerClasses)
        {
            if (Actor->IsA(ValidClass))
            {
                bValidClass = true;
                break;
            }
        }
        if (!bValidClass)
        {
            return false;
        }
    }

    return true;
}

// === OVERLAP EVENTS ===

void ACheckpoint::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (CanTrigger(OtherActor))
    {
        bActorInTrigger = true;
        CurrentTriggeringActor = OtherActor;
        
        // Calculate completion time
        float CompletionTime = GetWorld()->GetTimeSeconds() - TimeCreated;
        
        // Complete the checkpoint
        CompleteCheckpoint(OtherActor, CompletionTime);
        
        UE_LOG(LogTemp, Log, TEXT("?? Actor '%s' triggered checkpoint '%s'"), 
            *OtherActor->GetName(), *CheckpointName);
    }
}

void ACheckpoint::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor == CurrentTriggeringActor)
    {
        bActorInTrigger = false;
        CurrentTriggeringActor = nullptr;
        
        UE_LOG(LogTemp, VeryVerbose, TEXT("Actor '%s' left checkpoint '%s'"), 
            *OtherActor->GetName(), *CheckpointName);
    }
}

// === VISUAL FUNCTIONS ===

void ACheckpoint::UpdateVisualState()
{
    if (!CheckpointMesh) return;

    // Create dynamic material if needed
    UMaterialInstanceDynamic* DynamicMaterial = CheckpointMesh->CreateAndSetMaterialInstanceDynamic(0);
    if (!DynamicMaterial) return;

    // Get current color based on state
    FLinearColor CurrentColor = InactiveColor; // Initialize with default
    switch (CheckpointState)
    {
        case ECheckpointState::Inactive:
            CurrentColor = InactiveColor;
            break;
        case ECheckpointState::Active:
            CurrentColor = ActiveColor;
            break;
        case ECheckpointState::Completed:
            CurrentColor = CompletedColor;
            break;
    }

    // Add pulsing effect for active checkpoints
    if (CheckpointState == ECheckpointState::Active)
    {
        float PulseValue = FMath::Sin(GetWorld()->GetTimeSeconds() * PulseSpeed) * PulseIntensity + 1.f;
        CurrentColor = CurrentColor * PulseValue;
    }

    // Apply color to material
    DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), CurrentColor);
    DynamicMaterial->SetScalarParameterValue(TEXT("Emissive"), CheckpointState == ECheckpointState::Active ? 2.f : 0.5f);
}

void ACheckpoint::UpdateParticleEffects()
{
    if (!ParticleEffect) return;

    // Manage particle effects based on state
    switch (CheckpointState)
    {
        case ECheckpointState::Inactive:
            if (ParticleEffect->IsActive())
            {
                ParticleEffect->Deactivate();
            }
            break;
            
        case ECheckpointState::Active:
            if (!ParticleEffect->IsActive())
            {
                ParticleEffect->Activate();
            }
            // Modify particle color based on checkpoint type
            if (CheckpointType == ECheckpointType::Bonus)
            {
                ParticleEffect->SetColorParameter(TEXT("Color"), FLinearColor::Yellow);
            }
            else if (CheckpointType == ECheckpointType::TimeBonus)
            {
                ParticleEffect->SetColorParameter(TEXT("Color"), FLinearColor::Blue);
            }
            break;
            
        case ECheckpointState::Completed:
            // Keep particles active briefly after completion
            break;
    }
}

void ACheckpoint::PlayTriggerEffects()
{
    // Play audio effect
    if (AudioComponent && AudioComponent->GetSound())
    {
        AudioComponent->Play();
    }

    // Enhanced particle burst for completion
    if (ParticleEffect)
    {
        ParticleEffect->SetFloatParameter(TEXT("BurstIntensity"), 2.f);
        
        // Reset burst intensity after a delay
        FTimerHandle ResetTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(
            ResetTimerHandle,
            [this]()
            {
                if (ParticleEffect)
                {
                    ParticleEffect->SetFloatParameter(TEXT("BurstIntensity"), 1.f);
                }
            },
            0.5f,
            false
        );
    }
}