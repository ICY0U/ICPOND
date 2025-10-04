#include "TimeTrialStartRing.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"
#include "BoatPawn.h"
#include "CheckpointSystem.h"
#include "EngineUtils.h"

ATimeTrialStartRing::ATimeTrialStartRing()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create root component
    USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    // Create ring mesh (using torus/cylinder)
    RingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RingMesh"));
    RingMesh->SetupAttachment(RootComponent);
    RingMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RingMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

    // Try to load a torus mesh for the ring
    static ConstructorHelpers::FObjectFinder<UStaticMesh> TorusMeshObj(TEXT("/Engine/BasicShapes/Cylinder"));
    if (TorusMeshObj.Succeeded())
    {
        RingMesh->SetStaticMesh(TorusMeshObj.Object);
    }

    // Create trigger volume
    RingTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RingTrigger"));
    RingTrigger->SetupAttachment(RootComponent);
    RingTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    RingTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    RingTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    RingTrigger->SetGenerateOverlapEvents(true);

    // Bind overlap
    RingTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATimeTrialStartRing::OnRingBeginOverlap);
}

void ATimeTrialStartRing::BeginPlay()
{
    Super::BeginPlay();
    
    // Setup ring geometry
    if (RingMesh)
    {
        // Scale to create ring shape
        FVector Scale;
        Scale.X = RingRadius / 50.f;
        Scale.Y = RingRadius / 50.f;
        Scale.Z = RingThickness / 100.f;
        RingMesh->SetWorldScale3D(Scale);
        
        // Rotate to stand upright
        RingMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
    }
    
    // Setup trigger
    if (RingTrigger)
    {
        FVector TriggerExtent;
        TriggerExtent.X = RingRadius * 1.2f;
        TriggerExtent.Y = RingRadius * 1.2f;
        TriggerExtent.Z = RingRadius * 0.8f;
        RingTrigger->SetBoxExtent(TriggerExtent);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("?? START RING READY!"));
    UE_LOG(LogTemp, Warning, TEXT("   - Radius: %.0f"), RingRadius);
    UE_LOG(LogTemp, Warning, TEXT("   - Auto Start Time Trial: %s"), bAutoStartTimeTrial ? TEXT("YES") : TEXT("NO"));
    UE_LOG(LogTemp, Warning, TEXT("   - Auto Start Checkpoint Race: %s"), bAutoStartCheckpointRace ? TEXT("YES") : TEXT("NO"));

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, 
            TEXT("?? START RING ACTIVE! Drive through to begin!"));
    }
}

void ATimeTrialStartRing::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Pulse animation
    PulseTimer += DeltaTime * 2.f;
    float PulseValue = (FMath::Sin(PulseTimer) + 1.f) * 0.5f; // 0 to 1
    
    // Draw debug visuals
    if (bShowDebugVisuals && GetWorld())
    {
        FVector Location = GetActorLocation();
        FVector ForwardDir = GetActorForwardVector();
        
        // Draw ring outline
        FColor RingDebugColor = FColor::Green;
        if (bHasTriggered && bOnlyTriggerOnce)
        {
            RingDebugColor = FColor::Silver; // Gray when used
        }
        else
        {
            // Pulsing effect
            uint8 Intensity = (uint8)(155 + (PulseValue * 100));
            RingDebugColor = FColor(0, Intensity, 0);
        }
        
        // Draw the ring as a circle
        DrawDebugCircle(GetWorld(), Location, RingRadius, 32, RingDebugColor, false, -1.f, 0, 5.f,
            FVector(0, 1, 0), FVector(1, 0, 0), false);
        
        // Draw center cross
        DrawDebugLine(GetWorld(), 
            Location - ForwardDir * RingRadius * 0.3f,
            Location + ForwardDir * RingRadius * 0.3f,
            FColor::Yellow, false, -1.f, 0, 3.f);
        
        // Draw direction arrow
        FVector ArrowStart = Location + ForwardDir * (RingRadius + 200.f);
        FVector ArrowEnd = Location + ForwardDir * RingRadius;
        DrawDebugDirectionalArrow(GetWorld(), ArrowStart, ArrowEnd, 
            100.f, FColor::Green, false, -1.f, 0, 5.f);
        
        // Draw info text
        FString InfoText = bAutoStartTimeTrial ? TEXT("START RING\n[Time Trial]") : TEXT("START RING\n[Checkpoint Race]");
        if (bHasTriggered && bOnlyTriggerOnce)
        {
            InfoText = TEXT("START RING\n[USED]");
        }
        DrawDebugString(GetWorld(), Location + FVector(0, 0, RingRadius + 100), InfoText, 
            nullptr, FColor::White, 0.f, true, 1.5f);
    }
}

void ATimeTrialStartRing::OnRingBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor) return;
    
    // Check if already triggered (if set to trigger once)
    if (bOnlyTriggerOnce && bHasTriggered) 
    {
        UE_LOG(LogTemp, Log, TEXT("?? Start ring already triggered, ignoring"));
        return;
    }

    // Check if it's a pawn (boat)
    APawn* Pawn = Cast<APawn>(OtherActor);
    if (Pawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("?? BOAT ENTERED START RING: %s"), *OtherActor->GetName());
        
        // Mark as triggered
        bHasTriggered = true;
        
        // Start race
        StartRaceForBoat(OtherActor);
        
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("?? RACE STARTED!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("?? Non-pawn actor entered start ring: %s"), *OtherActor->GetName());
    }
}

void ATimeTrialStartRing::StartRaceForBoat(AActor* BoatActor)
{
    if (!BoatActor) return;

    // Try to cast to BoatPawn using direct include
    ABoatPawn* Boat = Cast<ABoatPawn>(BoatActor);
    
    if (Boat)
    {
        UE_LOG(LogTemp, Warning, TEXT("? Found BoatPawn, starting race systems..."));
        
        // Start Time Trial if enabled
        if (bAutoStartTimeTrial)
        {
            Boat->StartTimeTrial(TimeTrialDuration);
            UE_LOG(LogTemp, Warning, TEXT("?? Started Time Trial: %.0f seconds"), TimeTrialDuration);
            
            if (GEngine)
            {
                FString TimeTrialMsg = FString::Printf(TEXT("?? TIME TRIAL STARTED! Duration: %.0f sec"), TimeTrialDuration);
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TimeTrialMsg);
            }
        }
        
        // Start Checkpoint Race if enabled
        if (bAutoStartCheckpointRace)
        {
            // Try to find and start checkpoint system
            Boat->StartCheckpointRace();
            UE_LOG(LogTemp, Warning, TEXT("?? Started Checkpoint Race"));
            
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("?? CHECKPOINT RACE STARTED!"));
            }
        }
        
        if (GEngine)
        {
            FString StatusMsg = FString::Printf(
                TEXT("?? RACE ACTIVE!\nTime Trial: %s\nCheckpoints: %s"),
                bAutoStartTimeTrial ? TEXT("YES") : TEXT("NO"),
                bAutoStartCheckpointRace ? TEXT("YES") : TEXT("NO")
            );
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, StatusMsg);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("? Could not cast actor to BoatPawn! Actor: %s"), *BoatActor->GetName());
        
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, 
                TEXT("? Start ring needs a BoatPawn to work!"));
        }
    }
}