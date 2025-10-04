#include "ArcadePowerUp.h"
#include "BoatPawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"

AArcadePowerUp::AArcadePowerUp()
{
    PrimaryActorTick.bCanEverTick = true;

    // Collision sphere for pickup detection
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    SetRootComponent(CollisionSphere);
    CollisionSphere->SetSphereRadius(80.f);
    CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AArcadePowerUp::OnSphereBeginOverlap);

    // Visual mesh component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(CollisionSphere);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    
    // Load a basic sphere mesh for the powerup
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(SphereMesh.Object);
        MeshComponent->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
    }

    // Glow particles for visual appeal
    GlowParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GlowParticles"));
    GlowParticles->SetupAttachment(MeshComponent);
    GlowParticles->bAutoActivate = true;
    
    // Try to load a sparkle effect
    static ConstructorHelpers::FObjectFinder<UParticleSystem> SparkleEffect(TEXT("/Engine/VFX/P_Sparks"));
    if (SparkleEffect.Succeeded())
    {
        GlowParticles->SetTemplate(SparkleEffect.Object);
    }

    // Ambient audio for atmosphere
    AmbientAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientAudio"));
    AmbientAudio->SetupAttachment(MeshComponent);
    AmbientAudio->bAutoActivate = true;
    AmbientAudio->SetVolumeMultiplier(0.5f);
    
    // Try to load ambient sound
    static ConstructorHelpers::FObjectFinder<USoundCue> AmbientSound(TEXT("/Engine/EditorSounds/Notifications/CompileStart_Cue"));
    if (AmbientSound.Succeeded())
    {
        AmbientAudio->SetSound(AmbientSound.Object);
    }

    bIsCollected = false;
}

void AArcadePowerUp::BeginPlay()
{
    Super::BeginPlay();
    
    InitialZ = GetActorLocation().Z;
    LifeTime = 0.f;
    
    // Set initial material color based on power-up type
    if (MeshComponent)
    {
        UMaterialInstanceDynamic* DynamicMaterial = MeshComponent->CreateDynamicMaterialInstance(0);
        if (DynamicMaterial)
        {
            DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), GetPowerUpColor());
        }
    }
    
    UE_LOG(LogTemp, Log, TEXT("?? PowerUp spawned: %s"), *GetPowerUpName());
}

void AArcadePowerUp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (!bIsCollected)
    {
        LifeTime += DeltaTime;
        
        // Floating animation
        FVector CurrentLocation = GetActorLocation();
        float NewZ = InitialZ + FMath::Sin(LifeTime * FloatSpeed * 0.1f) * FloatAmplitude;
        SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, NewZ));
        
        // Rotation animation
        FRotator CurrentRotation = GetActorRotation();
        CurrentRotation.Yaw += RotationSpeed * DeltaTime;
        SetActorRotation(CurrentRotation);
        
        // Pulsing glow effect
        if (GlowParticles)
        {
            float PulseIntensity = 0.5f + (FMath::Sin(LifeTime * 3.f) * 0.5f);
            GlowParticles->SetFloatParameter(TEXT("Intensity"), PulseIntensity);
        }
    }
}

void AArcadePowerUp::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (bIsCollected) return;
    
    ABoatPawn* BoatPawn = Cast<ABoatPawn>(OtherActor);
    if (!BoatPawn) return;
    
    bIsCollected = true;
    PlayCollectionEffects();
    
    // Apply power-up effect based on type
    switch (PowerUpType)
    {
        case EPowerUpType::SpeedBoost:
        {
            // Temporarily increase max speed
            UE_LOG(LogTemp, Warning, TEXT("?? Speed Boost Collected!"));
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("?? SPEED BOOST!"));
            }
            // Note: You would implement temporary speed boost in BoatPawn
            break;
        }
        
        case EPowerUpType::BoostRefill:
        {
            // Refill boost energy
            UE_LOG(LogTemp, Warning, TEXT("? Boost Energy Refilled!"));
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("? BOOST REFILLED!"));
            }
            // Note: You would call BoatPawn->RefillBoostEnergy() here
            break;
        }
        
        case EPowerUpType::ScoreMultiplier:
        {
            UE_LOG(LogTemp, Warning, TEXT("? Score Multiplier Active!"));
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Magenta, TEXT("? 2X SCORE MULTIPLIER!"));
            }
            // Note: You would implement score multiplier in BoatPawn
            break;
        }
        
        case EPowerUpType::JumpPower:
        {
            UE_LOG(LogTemp, Warning, TEXT("?? Jump Power Enhanced!"));
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("?? MEGA JUMP!"));
            }
            // Note: You would implement enhanced jump force in BoatPawn
            break;
        }
        
        case EPowerUpType::Invincibility:
        {
            UE_LOG(LogTemp, Warning, TEXT("??? Invincibility Active!"));
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("??? INVINCIBLE!"));
            }
            // Note: You would implement invincibility in BoatPawn
            break;
        }
        
        case EPowerUpType::MegaPoints:
        {
            UE_LOG(LogTemp, Warning, TEXT("?? Mega Points Collected!"));
            if (GEngine)
            {
                FString PointsMessage = FString::Printf(TEXT("?? +%d MEGA POINTS!"), PointsValue);
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, PointsMessage);
            }
            // Add points directly (this works with current BoatPawn implementation)
            // BoatPawn->AddScore(PointsValue, GetPowerUpName());
            break;
        }
    }
    
    // Hide the power-up and set respawn timer
    SetPowerUpVisibility(false);
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AArcadePowerUp::OnRespawn, RespawnTime, false);
}

void AArcadePowerUp::SetPowerUpVisibility(bool bVisible)
{
    SetActorHiddenInGame(!bVisible);
    SetActorEnableCollision(bVisible);
    
    if (GlowParticles)
    {
        if (bVisible)
        {
            GlowParticles->Activate();
        }
        else
        {
            GlowParticles->Deactivate();
        }
    }
    
    if (AmbientAudio)
    {
        if (bVisible)
        {
            AmbientAudio->Play();
        }
        else
        {
            AmbientAudio->Stop();
        }
    }
}

void AArcadePowerUp::OnRespawn()
{
    bIsCollected = false;
    LifeTime = 0.f;
    SetPowerUpVisibility(true);
    
    UE_LOG(LogTemp, Log, TEXT("?? PowerUp respawned: %s"), *GetPowerUpName());
}

void AArcadePowerUp::PlayCollectionEffects()
{
    // Play collection particle burst
    if (GlowParticles)
    {
        GlowParticles->SetFloatParameter(TEXT("BurstIntensity"), 3.f);
    }
    
    // Play collection sound
    if (AmbientAudio)
    {
        AmbientAudio->SetPitchMultiplier(2.f);
        AmbientAudio->SetVolumeMultiplier(1.f);
    }
}

FLinearColor AArcadePowerUp::GetPowerUpColor() const
{
    switch (PowerUpType)
    {
        case EPowerUpType::SpeedBoost:      return FLinearColor::Red;
        case EPowerUpType::BoostRefill:     return FLinearColor::Blue;
        case EPowerUpType::ScoreMultiplier: return FLinearColor(1.f, 0.5f, 1.f); // Magenta
        case EPowerUpType::JumpPower:       return FLinearColor::Green;
        case EPowerUpType::Invincibility:   return FLinearColor::White;
        case EPowerUpType::MegaPoints:      return FLinearColor::Yellow;
        default:                           return FLinearColor::White;
    }
}

FString AArcadePowerUp::GetPowerUpName() const
{
    switch (PowerUpType)
    {
        case EPowerUpType::SpeedBoost:      return TEXT("Speed Boost");
        case EPowerUpType::BoostRefill:     return TEXT("Boost Refill");
        case EPowerUpType::ScoreMultiplier: return TEXT("Score Multiplier");
        case EPowerUpType::JumpPower:       return TEXT("Jump Power");
        case EPowerUpType::Invincibility:   return TEXT("Invincibility");
        case EPowerUpType::MegaPoints:      return TEXT("Mega Points");
        default:                           return TEXT("Unknown PowerUp");
    }
}