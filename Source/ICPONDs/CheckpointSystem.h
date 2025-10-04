#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.h"
#include "CheckpointSystem.generated.h"

UENUM(BlueprintType)
enum class ECheckpointSystemMode : uint8
{
    Sequential,     // Checkpoints must be completed in order
    FreeForm,       // Checkpoints can be completed in any order
    TimeTrial,      // Timed race through checkpoints
    Collection      // Collect all checkpoints (like coins)
};

UENUM(BlueprintType)
enum class ECheckpointSystemState : uint8
{
    Inactive,
    Active,
    Completed,
    Failed
};

USTRUCT(BlueprintType)
struct FCheckpointRace
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    float StartTime = 0.f;

    UPROPERTY(BlueprintReadWrite)
    float EndTime = 0.f;

    UPROPERTY(BlueprintReadWrite)
    float TotalTime = 0.f;

    UPROPERTY(BlueprintReadWrite)
    int32 CheckpointsCompleted = 0;

    UPROPERTY(BlueprintReadWrite)
    int32 TotalCheckpoints = 0;

    UPROPERTY(BlueprintReadWrite)
    int32 TotalScore = 0;

    UPROPERTY(BlueprintReadWrite)
    AActor* ParticipatingActor = nullptr;

    FCheckpointRace()
    {
        StartTime = 0.f;
        EndTime = 0.f;
        TotalTime = 0.f;
        CheckpointsCompleted = 0;
        TotalCheckpoints = 0;
        TotalScore = 0;
        ParticipatingActor = nullptr;
    }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCheckpointSystemEvent, ECheckpointSystemState, SystemState, const FCheckpointRace&, RaceData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCheckpointCompleted, ACheckpoint*, Checkpoint, AActor*, TriggeringActor, int32, CheckpointNumber);

UCLASS()
class ICPONDS_API ACheckpointSystem : public AActor
{
    GENERATED_BODY()
    
public:    
    ACheckpointSystem();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    // === SYSTEM PROPERTIES ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System")
    ECheckpointSystemMode SystemMode = ECheckpointSystemMode::Sequential;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System")
    ECheckpointSystemState SystemState = ECheckpointSystemState::Inactive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System")
    TArray<ACheckpoint*> Checkpoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System")
    bool bAutoStartOnBeginPlay = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System")
    bool bAutoActivateCheckpoints = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System")
    float TimeLimit = 0.f; // 0 = no time limit

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System")
    int32 RequiredCheckpoints = -1; // -1 = all checkpoints required

    // === SCORING PROPERTIES ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System|Scoring")
    int32 CheckpointBaseScore = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System|Scoring")
    int32 CompletionBonusScore = 500;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint System|Scoring")
    float TimeScoreMultiplier = 1.f; // Points per second under time limit

    // === EVENTS ===
    UPROPERTY(BlueprintAssignable, Category="Checkpoint System|Events")
    FOnCheckpointSystemEvent OnSystemStateChanged;

    UPROPERTY(BlueprintAssignable, Category="Checkpoint System|Events")
    FOnCheckpointCompleted OnCheckpointCompleted;

    // === PUBLIC FUNCTIONS ===
    UFUNCTION(BlueprintCallable, Category="Checkpoint System")
    void StartSystem(AActor* ParticipatingActor = nullptr);

    UFUNCTION(BlueprintCallable, Category="Checkpoint System")
    void StopSystem();

    UFUNCTION(BlueprintCallable, Category="Checkpoint System")
    void ResetSystem();

    UFUNCTION(BlueprintCallable, Category="Checkpoint System")
    void AddCheckpoint(ACheckpoint* NewCheckpoint, int32 InsertIndex = -1);

    UFUNCTION(BlueprintCallable, Category="Checkpoint System")
    void RemoveCheckpoint(ACheckpoint* CheckpointToRemove);

    UFUNCTION(BlueprintCallable, Category="Checkpoint System")
    void SortCheckpointsByID();

    UFUNCTION(BlueprintCallable, Category="Checkpoint System")
    void AutoDiscoverCheckpoints();

    // === QUERY FUNCTIONS ===
    UFUNCTION(BlueprintPure, Category="Checkpoint System")
    int32 GetCompletedCheckpointCount() const;

    UFUNCTION(BlueprintPure, Category="Checkpoint System")
    int32 GetTotalCheckpointCount() const { return Checkpoints.Num(); }

    UFUNCTION(BlueprintPure, Category="Checkpoint System")
    float GetCompletionPercentage() const;

    UFUNCTION(BlueprintPure, Category="Checkpoint System")
    ACheckpoint* GetNextActiveCheckpoint() const;

    UFUNCTION(BlueprintPure, Category="Checkpoint System")
    ACheckpoint* GetCurrentCheckpoint() const;

    UFUNCTION(BlueprintPure, Category="Checkpoint System")
    bool IsSystemComplete() const;

    UFUNCTION(BlueprintPure, Category="Checkpoint System")
    float GetElapsedTime() const;

    UFUNCTION(BlueprintPure, Category="Checkpoint System")
    float GetRemainingTime() const;

    UFUNCTION(BlueprintPure, Category="Checkpoint System")
    const FCheckpointRace& GetCurrentRaceData() const { return CurrentRace; }

    // === INTEGRATION FUNCTIONS FOR TIME TRIALS ===
    UFUNCTION(BlueprintCallable, Category="Checkpoint System|Time Trial")
    void IntegrateWithTimeTrial(AActor* BoatPawn);

    UFUNCTION(BlueprintCallable, Category="Checkpoint System|Time Trial")
    void OnTimeTrialStarted();

    UFUNCTION(BlueprintCallable, Category="Checkpoint System|Time Trial")
    void OnTimeTrialEnded();

protected:
    // === INTERNAL STATE ===
    FCheckpointRace CurrentRace;
    int32 CurrentCheckpointIndex = 0;
    AActor* TrackedActor = nullptr;

    // === CHECKPOINT EVENT HANDLERS ===
    UFUNCTION()
    void OnCheckpointTriggered(ACheckpoint* Checkpoint, AActor* TriggeringActor, float CompletionTime);

    // === INTERNAL FUNCTIONS ===
    void UpdateSystemState();
    void ActivateNextCheckpoint();
    void CheckCompletionConditions();
    void CalculateFinalScore();
    void ShowSystemUI();

private:
    // === UI UPDATE TIMER ===
    float UIUpdateTimer = 0.f;
    const float UIUpdateInterval = 0.5f;
};