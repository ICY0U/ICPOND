#include "CheckpointSystem.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "EngineUtils.h"

ACheckpointSystem::ACheckpointSystem()
{
    PrimaryActorTick.bCanEverTick = true;

    // === INITIALIZE DEFAULT VALUES ===
    SystemMode = ECheckpointSystemMode::Sequential;
    SystemState = ECheckpointSystemState::Inactive;
    bAutoStartOnBeginPlay = false;
    bAutoActivateCheckpoints = true;
    TimeLimit = 0.f;
    RequiredCheckpoints = -1;
    
    CheckpointBaseScore = 100;
    CompletionBonusScore = 500;
    TimeScoreMultiplier = 1.f;
    
    CurrentCheckpointIndex = 0;
    TrackedActor = nullptr;
}

void ACheckpointSystem::BeginPlay()
{
    Super::BeginPlay();

    // Auto-discover checkpoints if none are assigned
    if (Checkpoints.Num() == 0)
    {
        AutoDiscoverCheckpoints();
    }

    // Sort checkpoints by ID for sequential mode
    if (SystemMode == ECheckpointSystemMode::Sequential)
    {
        SortCheckpointsByID();
    }

    // Bind to checkpoint events
    for (ACheckpoint* Checkpoint : Checkpoints)
    {
        if (Checkpoint)
        {
            Checkpoint->OnCheckpointTriggered.AddDynamic(this, &ACheckpointSystem::OnCheckpointTriggered);
        }
    }

    // Auto-start if configured
    if (bAutoStartOnBeginPlay)
    {
        StartSystem();
    }

    UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint System initialized with %d checkpoints in %s mode"), 
        Checkpoints.Num(), 
        SystemMode == ECheckpointSystemMode::Sequential ? TEXT("SEQUENTIAL") : 
        SystemMode == ECheckpointSystemMode::FreeForm ? TEXT("FREEFORM") :
        SystemMode == ECheckpointSystemMode::TimeTrial ? TEXT("TIME TRIAL") : TEXT("COLLECTION"));
}

void ACheckpointSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (SystemState == ECheckpointSystemState::Active)
    {
        UpdateSystemState();
        
        // Update UI periodically
        UIUpdateTimer += DeltaTime;
        if (UIUpdateTimer >= UIUpdateInterval)
        {
            ShowSystemUI();
            UIUpdateTimer = 0.f;
        }
    }
}

// === PUBLIC FUNCTIONS ===

void ACheckpointSystem::StartSystem(AActor* ParticipatingActor)
{
    if (SystemState == ECheckpointSystemState::Active)
    {
        UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint System already active!"));
        return;
    }

    // Initialize race data
    CurrentRace = FCheckpointRace();
    CurrentRace.StartTime = GetWorld()->GetTimeSeconds();
    CurrentRace.TotalCheckpoints = Checkpoints.Num();
    CurrentRace.ParticipatingActor = ParticipatingActor;
    TrackedActor = ParticipatingActor;

    // Set required checkpoints if not specified
    if (RequiredCheckpoints <= 0)
    {
        RequiredCheckpoints = Checkpoints.Num();
    }

    // Reset all checkpoints
    for (ACheckpoint* Checkpoint : Checkpoints)
    {
        if (Checkpoint)
        {
            Checkpoint->ResetCheckpoint();
        }
    }

    // Activate checkpoints based on mode
    switch (SystemMode)
    {
        case ECheckpointSystemMode::Sequential:
        case ECheckpointSystemMode::TimeTrial:
            CurrentCheckpointIndex = 0;
            ActivateNextCheckpoint();
            break;
            
        case ECheckpointSystemMode::FreeForm:
        case ECheckpointSystemMode::Collection:
            // Activate all checkpoints
            for (ACheckpoint* Checkpoint : Checkpoints)
            {
                if (Checkpoint)
                {
                    Checkpoint->ActivateCheckpoint();
                }
            }
            break;
    }

    SystemState = ECheckpointSystemState::Active;
    OnSystemStateChanged.Broadcast(SystemState, CurrentRace);

    UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint System STARTED! Mode: %s, Checkpoints: %d"), 
        SystemMode == ECheckpointSystemMode::Sequential ? TEXT("Sequential") : 
        SystemMode == ECheckpointSystemMode::FreeForm ? TEXT("FreeForm") :
        SystemMode == ECheckpointSystemMode::TimeTrial ? TEXT("TimeTrial") : TEXT("Collection"),
        Checkpoints.Num());

    if (GEngine)
    {
        FString StartMessage = FString::Printf(TEXT("?? CHECKPOINT RACE STARTED! %d checkpoints to complete"), RequiredCheckpoints);
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, StartMessage);
    }
}

void ACheckpointSystem::StopSystem()
{
    if (SystemState != ECheckpointSystemState::Active)
    {
        return;
    }

    CurrentRace.EndTime = GetWorld()->GetTimeSeconds();
    CurrentRace.TotalTime = CurrentRace.EndTime - CurrentRace.StartTime;
    
    CalculateFinalScore();

    SystemState = ECheckpointSystemState::Completed;
    OnSystemStateChanged.Broadcast(SystemState, CurrentRace);

    // Deactivate all checkpoints
    for (ACheckpoint* Checkpoint : Checkpoints)
    {
        if (Checkpoint)
        {
            Checkpoint->DeactivateCheckpoint();
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint System COMPLETED! Time: %.2f, Score: %d, Checkpoints: %d/%d"), 
        CurrentRace.TotalTime, CurrentRace.TotalScore, CurrentRace.CheckpointsCompleted, CurrentRace.TotalCheckpoints);

    if (GEngine)
    {
        FString CompletionMessage = FString::Printf(
            TEXT("?? RACE COMPLETE!\nTime: %.2f seconds\nScore: %d\nCheckpoints: %d/%d"), 
            CurrentRace.TotalTime, CurrentRace.TotalScore, 
            CurrentRace.CheckpointsCompleted, CurrentRace.TotalCheckpoints);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, CompletionMessage);
    }
}

void ACheckpointSystem::ResetSystem()
{
    SystemState = ECheckpointSystemState::Inactive;
    CurrentCheckpointIndex = 0;
    CurrentRace = FCheckpointRace();
    TrackedActor = nullptr;

    // Reset all checkpoints
    for (ACheckpoint* Checkpoint : Checkpoints)
    {
        if (Checkpoint)
        {
            Checkpoint->ResetCheckpoint();
        }
    }

    OnSystemStateChanged.Broadcast(SystemState, CurrentRace);
    UE_LOG(LogTemp, Log, TEXT("?? Checkpoint System RESET"));
}

void ACheckpointSystem::AddCheckpoint(ACheckpoint* NewCheckpoint, int32 InsertIndex)
{
    if (!NewCheckpoint)
    {
        return;
    }

    if (InsertIndex >= 0 && InsertIndex < Checkpoints.Num())
    {
        Checkpoints.Insert(NewCheckpoint, InsertIndex);
    }
    else
    {
        Checkpoints.Add(NewCheckpoint);
    }

    // Bind to checkpoint events
    NewCheckpoint->OnCheckpointTriggered.AddDynamic(this, &ACheckpointSystem::OnCheckpointTriggered);

    UE_LOG(LogTemp, Log, TEXT("? Added checkpoint '%s' to system"), *NewCheckpoint->CheckpointName);
}

void ACheckpointSystem::RemoveCheckpoint(ACheckpoint* CheckpointToRemove)
{
    if (!CheckpointToRemove)
    {
        return;
    }

    // Unbind events
    CheckpointToRemove->OnCheckpointTriggered.RemoveDynamic(this, &ACheckpointSystem::OnCheckpointTriggered);
    
    Checkpoints.Remove(CheckpointToRemove);
    UE_LOG(LogTemp, Log, TEXT("? Removed checkpoint '%s' from system"), *CheckpointToRemove->CheckpointName);
}

void ACheckpointSystem::SortCheckpointsByID()
{
    Checkpoints.Sort([](const ACheckpoint& A, const ACheckpoint& B) {
        return A.CheckpointID < B.CheckpointID;
    });
    
    UE_LOG(LogTemp, Log, TEXT("?? Checkpoints sorted by ID"));
}

void ACheckpointSystem::AutoDiscoverCheckpoints()
{
    Checkpoints.Empty();

    // Find all checkpoint actors in the world
    for (TActorIterator<ACheckpoint> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
    {
        ACheckpoint* Checkpoint = *ActorIterator;
        if (Checkpoint)
        {
            Checkpoints.Add(Checkpoint);
        }
    }

    // Sort by ID for consistent ordering
    SortCheckpointsByID();

    UE_LOG(LogTemp, Warning, TEXT("?? Auto-discovered %d checkpoints"), Checkpoints.Num());
}

// === QUERY FUNCTIONS ===

int32 ACheckpointSystem::GetCompletedCheckpointCount() const
{
    int32 Count = 0;
    for (const ACheckpoint* Checkpoint : Checkpoints)
    {
        if (Checkpoint && Checkpoint->IsCompleted())
        {
            Count++;
        }
    }
    return Count;
}

float ACheckpointSystem::GetCompletionPercentage() const
{
    if (Checkpoints.Num() == 0)
    {
        return 0.f;
    }
    
    return (float)GetCompletedCheckpointCount() / (float)RequiredCheckpoints * 100.f;
}

ACheckpoint* ACheckpointSystem::GetNextActiveCheckpoint() const
{
    for (ACheckpoint* Checkpoint : Checkpoints)
    {
        if (Checkpoint && Checkpoint->IsActive())
        {
            return Checkpoint;
        }
    }
    return nullptr;
}

ACheckpoint* ACheckpointSystem::GetCurrentCheckpoint() const
{
    if (CurrentCheckpointIndex >= 0 && CurrentCheckpointIndex < Checkpoints.Num())
    {
        return Checkpoints[CurrentCheckpointIndex];
    }
    return nullptr;
}

bool ACheckpointSystem::IsSystemComplete() const
{
    return GetCompletedCheckpointCount() >= RequiredCheckpoints;
}

float ACheckpointSystem::GetElapsedTime() const
{
    if (SystemState == ECheckpointSystemState::Active)
    {
        return GetWorld()->GetTimeSeconds() - CurrentRace.StartTime;
    }
    return CurrentRace.TotalTime;
}

float ACheckpointSystem::GetRemainingTime() const
{
    if (TimeLimit <= 0.f)
    {
        return -1.f; // No time limit
    }
    
    return FMath::Max(0.f, TimeLimit - GetElapsedTime());
}

// === TIME TRIAL INTEGRATION ===

void ACheckpointSystem::IntegrateWithTimeTrial(AActor* BoatPawn)
{
    TrackedActor = BoatPawn;
    SystemMode = ECheckpointSystemMode::TimeTrial;
    
    UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint System integrated with Time Trial mode"));
}

void ACheckpointSystem::OnTimeTrialStarted()
{
    StartSystem(TrackedActor);
}

void ACheckpointSystem::OnTimeTrialEnded()
{
    StopSystem();
}

// === EVENT HANDLERS ===

void ACheckpointSystem::OnCheckpointTriggered(ACheckpoint* Checkpoint, AActor* TriggeringActor, float CompletionTime)
{
    if (!Checkpoint || SystemState != ECheckpointSystemState::Active)
    {
        return;
    }

    // Update race data
    CurrentRace.CheckpointsCompleted++;
    CurrentRace.TotalScore += CheckpointBaseScore;

    // Add checkpoint-specific bonus
    if (Checkpoint->BonusPoints > 0)
    {
        CurrentRace.TotalScore += Checkpoint->BonusPoints;
    }

    // Broadcast checkpoint completion
    OnCheckpointCompleted.Broadcast(Checkpoint, TriggeringActor, CurrentRace.CheckpointsCompleted);

    UE_LOG(LogTemp, Warning, TEXT("? Checkpoint %d completed! Total: %d/%d"), 
        Checkpoint->CheckpointID, CurrentRace.CheckpointsCompleted, RequiredCheckpoints);

    // Handle different system modes
    switch (SystemMode)
    {
        case ECheckpointSystemMode::Sequential:
        case ECheckpointSystemMode::TimeTrial:
            ActivateNextCheckpoint();
            break;
            
        case ECheckpointSystemMode::FreeForm:
        case ECheckpointSystemMode::Collection:
            // All checkpoints remain active
            break;
    }

    CheckCompletionConditions();
}

// === INTERNAL FUNCTIONS ===

void ACheckpointSystem::UpdateSystemState()
{
    // Check time limit
    if (TimeLimit > 0.f && GetElapsedTime() >= TimeLimit)
    {
        SystemState = ECheckpointSystemState::Failed;
        OnSystemStateChanged.Broadcast(SystemState, CurrentRace);
        
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("? TIME'S UP! Checkpoint race failed."));
        }
        
        StopSystem();
        return;
    }

    // Update current race time
    if (SystemState == ECheckpointSystemState::Active)
    {
        CurrentRace.TotalTime = GetElapsedTime();
    }
}

void ACheckpointSystem::ActivateNextCheckpoint()
{
    if (SystemMode != ECheckpointSystemMode::Sequential && SystemMode != ECheckpointSystemMode::TimeTrial)
    {
        return;
    }

    // Find next checkpoint to activate
    for (int32 i = CurrentCheckpointIndex; i < Checkpoints.Num(); i++)
    {
        ACheckpoint* Checkpoint = Checkpoints[i];
        if (Checkpoint && !Checkpoint->IsCompleted())
        {
            Checkpoint->ActivateCheckpoint();
            CurrentCheckpointIndex = i;
            break;
        }
    }
}

void ACheckpointSystem::CheckCompletionConditions()
{
    if (IsSystemComplete())
    {
        StopSystem();
    }
}

void ACheckpointSystem::CalculateFinalScore()
{
    // Add completion bonus
    if (IsSystemComplete())
    {
        CurrentRace.TotalScore += CompletionBonusScore;
    }

    // Add time bonus (if completed under time limit)
    if (TimeLimit > 0.f && CurrentRace.TotalTime < TimeLimit)
    {
        float TimeBonusSeconds = TimeLimit - CurrentRace.TotalTime;
        int32 TimeBonus = FMath::RoundToInt(TimeBonusSeconds * TimeScoreMultiplier);
        CurrentRace.TotalScore += TimeBonus;
    }
}

void ACheckpointSystem::ShowSystemUI()
{
    if (!GEngine || SystemState != ECheckpointSystemState::Active)
    {
        return;
    }

    // Format time display
    float ElapsedTime = GetElapsedTime();
    int32 Minutes = FMath::FloorToInt(ElapsedTime / 60.f);
    int32 Seconds = FMath::FloorToInt(ElapsedTime) % 60;
    int32 Milliseconds = FMath::FloorToInt((ElapsedTime - FMath::FloorToInt(ElapsedTime)) * 100);

    FString TimeString = FString::Printf(TEXT("%02d:%02d.%02d"), Minutes, Seconds, Milliseconds);

    // Create status display
    FString StatusMessage = FString::Printf(
        TEXT("?? CHECKPOINT RACE | %s | %d/%d | Score: %d"), 
        *TimeString, 
        CurrentRace.CheckpointsCompleted, 
        RequiredCheckpoints,
        CurrentRace.TotalScore
    );

    // Add time limit warning if applicable
    if (TimeLimit > 0.f)
    {
        float RemainingTime = GetRemainingTime();
        if (RemainingTime <= 10.f)
        {
            FString WarningMsg = FString::Printf(TEXT("?? TIME RUNNING OUT: %.1f seconds!"), RemainingTime);
            GEngine->AddOnScreenDebugMessage(997, 0.6f, FColor::Red, WarningMsg);
        }
    }

    GEngine->AddOnScreenDebugMessage(996, 0.6f, FColor::Orange, StatusMessage);
}