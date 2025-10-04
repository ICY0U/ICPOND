#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CheckpointSystemInterface.generated.h"

class ACheckpointSystem;
class ACheckpoint;

UINTERFACE(MinimalAPI, Blueprintable)
class UCheckpointSystemInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * Interface for actors that can interact with the checkpoint system
 * This allows the boat pawn (or any other actor) to integrate with checkpoints
 * without tight coupling
 */
class ICPONDS_API ICheckpointSystemInterface
{
    GENERATED_BODY()

public:
    // === CHECKPOINT SYSTEM EVENTS ===
    
    /** Called when a checkpoint race starts */
    UFUNCTION(BlueprintImplementableEvent, Category="Checkpoint Interface")
    void OnCheckpointRaceStarted(ACheckpointSystem* CheckpointSystem);

    /** Called when a checkpoint race ends */
    UFUNCTION(BlueprintImplementableEvent, Category="Checkpoint Interface")
    void OnCheckpointRaceEnded(ACheckpointSystem* CheckpointSystem, bool bCompleted, float TotalTime, int32 FinalScore);

    /** Called when this actor completes a checkpoint */
    UFUNCTION(BlueprintImplementableEvent, Category="Checkpoint Interface")
    void OnCheckpointCompleted(ACheckpoint* Checkpoint, int32 CheckpointNumber, float CompletionTime);

    /** Called when this actor gets a checkpoint bonus (points, time, etc.) */
    UFUNCTION(BlueprintImplementableEvent, Category="Checkpoint Interface")
    void OnCheckpointBonus(ACheckpoint* Checkpoint, float BonusPoints, float BonusTime);

    // === C++ IMPLEMENTATIONS (OPTIONAL OVERRIDES) ===
    
    /** C++ version of checkpoint race started event */
    virtual void NotifyCheckpointRaceStarted(ACheckpointSystem* CheckpointSystem) {}

    /** C++ version of checkpoint race ended event */
    virtual void NotifyCheckpointRaceEnded(ACheckpointSystem* CheckpointSystem, bool bCompleted, float TotalTime, int32 FinalScore) {}

    /** C++ version of checkpoint completed event */
    virtual void NotifyCheckpointCompleted(ACheckpoint* Checkpoint, int32 CheckpointNumber, float CompletionTime) {}

    /** C++ version of checkpoint bonus event */
    virtual void NotifyCheckpointBonus(ACheckpoint* Checkpoint, float BonusPoints, float BonusTime) {}

    // === QUERY FUNCTIONS ===
    
    /** Get the checkpoint system this actor is currently participating in */
    UFUNCTION(BlueprintImplementableEvent, Category="Checkpoint Interface")
    ACheckpointSystem* GetCurrentCheckpointSystem() const;

    /** Check if this actor is currently in a checkpoint race */
    UFUNCTION(BlueprintImplementableEvent, Category="Checkpoint Interface")
    bool IsInCheckpointRace() const;

    /** Get current checkpoint race progress (0.0 to 1.0) */
    UFUNCTION(BlueprintImplementableEvent, Category="Checkpoint Interface")
    float GetCheckpointRaceProgress() const;
};