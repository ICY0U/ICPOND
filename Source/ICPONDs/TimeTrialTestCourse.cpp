#include "TimeTrialTestCourse.h"
#include "CheckpointSystem.h"
#include "Checkpoint.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

ATimeTrialTestCourse::ATimeTrialTestCourse()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create root component
    USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);
}

void ATimeTrialTestCourse::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (!World) return;

    // Spawn checkpoints in a circle
    SpawnCheckpoints();

    // Setup checkpoint system
    SetupCheckpointSystem();

    UE_LOG(LogTemp, Warning, TEXT("?? TIME TRIAL TEST COURSE READY!"));
    UE_LOG(LogTemp, Warning, TEXT("   - %d Checkpoints spawned"), Checkpoints.Num());
    UE_LOG(LogTemp, Warning, TEXT("   - Time Limit: %.0f seconds"), TimeLimit);
    UE_LOG(LogTemp, Warning, TEXT("   - Course Radius: %.0f units"), CourseRadius);
    UE_LOG(LogTemp, Warning, TEXT("   - Debug Visuals: %s"), bShowDebugVisuals ? TEXT("ON") : TEXT("OFF"));

    if (GEngine)
    {
        FString SetupMessage = FString::Printf(
            TEXT("?? TIME TRIAL COURSE LOADED!\n%d Checkpoints | %.0f second limit\nPress T to start!"),
            Checkpoints.Num(), TimeLimit);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, SetupMessage);
    }
}

void ATimeTrialTestCourse::SpawnCheckpoints()
{
    UWorld* World = GetWorld();
    if (!World) return;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    Params.Owner = this;

    Checkpoints.Empty();

    for (int32 i = 0; i < NumberOfCheckpoints; ++i)
    {
        // Calculate position in a circle
        float Angle = (360.f / NumberOfCheckpoints) * i;
        FVector Offset = FVector(CourseRadius, 0.f, 0.f).RotateAngleAxis(Angle, FVector::UpVector);
        FVector SpawnLocation = GetActorLocation() + Offset + FVector(0.f, 0.f, CheckpointHeight);

        // Calculate rotation to face inward toward center
        FRotator SpawnRotation = FRotator::ZeroRotator;
        SpawnRotation.Yaw = Angle + 90.f; // Face tangent to circle

        // Spawn checkpoint
        ACheckpoint* NewCheckpoint = World->SpawnActor<ACheckpoint>(
            ACheckpoint::StaticClass(),
            SpawnLocation,
            SpawnRotation,
            Params
        );

        if (NewCheckpoint)
        {
            // Configure checkpoint
            NewCheckpoint->CheckpointID = i;
            NewCheckpoint->CheckpointName = FString::Printf(TEXT("Checkpoint %d"), i + 1);
            NewCheckpoint->TriggerRadius = 400.f;
            NewCheckpoint->BonusPoints = 100.f;

            // Set type based on position
            if (i == 0)
            {
                NewCheckpoint->CheckpointType = ECheckpointType::Start;
                NewCheckpoint->CheckpointName = TEXT("START");
                NewCheckpoint->ActiveColor = FLinearColor::Green;
            }
            else if (i == NumberOfCheckpoints - 1)
            {
                NewCheckpoint->CheckpointType = ECheckpointType::Finish;
                NewCheckpoint->CheckpointName = TEXT("FINISH");
                NewCheckpoint->ActiveColor = FLinearColor::Yellow;
            }
            else if (i == NumberOfCheckpoints / 2)
            {
                // Middle checkpoint gives time bonus
                NewCheckpoint->CheckpointType = ECheckpointType::TimeBonus;
                NewCheckpoint->BonusTime = 10.f;
                NewCheckpoint->CheckpointName = TEXT("TIME BONUS");
                NewCheckpoint->ActiveColor = FLinearColor::Blue;
            }
            else
            {
                NewCheckpoint->CheckpointType = ECheckpointType::Standard;
            }

            Checkpoints.Add(NewCheckpoint);

            UE_LOG(LogTemp, Log, TEXT("?? Spawned %s at angle %.0f°"), 
                *NewCheckpoint->CheckpointName, Angle);
        }
    }
}

void ATimeTrialTestCourse::SetupCheckpointSystem()
{
    UWorld* World = GetWorld();
    if (!World) return;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    Params.Owner = this;

    // Spawn checkpoint system
    CheckpointSystem = World->SpawnActor<ACheckpointSystem>(
        ACheckpointSystem::StaticClass(),
        GetActorLocation(),
        FRotator::ZeroRotator,
        Params
    );

    if (CheckpointSystem)
    {
        // Configure system
        CheckpointSystem->SystemMode = ECheckpointSystemMode::TimeTrial;
        CheckpointSystem->TimeLimit = TimeLimit;
        CheckpointSystem->bAutoStartOnBeginPlay = bAutoStartOnPlay;
        CheckpointSystem->bAutoActivateCheckpoints = true;
        CheckpointSystem->RequiredCheckpoints = NumberOfCheckpoints;
        
        // Scoring configuration
        CheckpointSystem->CheckpointBaseScore = 100;
        CheckpointSystem->CompletionBonusScore = 1000;
        CheckpointSystem->TimeScoreMultiplier = 10.f;

        // Add all checkpoints to the system
        for (ACheckpoint* Checkpoint : Checkpoints)
        {
            if (Checkpoint)
            {
                CheckpointSystem->AddCheckpoint(Checkpoint);
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("? Checkpoint System configured in Time Trial mode"));
        UE_LOG(LogTemp, Warning, TEXT("   - Time Limit: %.0f seconds"), TimeLimit);
        UE_LOG(LogTemp, Warning, TEXT("   - %d Checkpoints registered"), Checkpoints.Num());
    }
}