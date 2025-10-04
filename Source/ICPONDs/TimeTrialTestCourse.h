#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeTrialTestCourse.generated.h"

class ACheckpointSystem;
class ACheckpoint;

/**
 * Complete time trial test course that can be dropped into a level
 * Includes water plane, checkpoints, and checkpoint system pre-configured
 */
UCLASS()
class ICPONDS_API ATimeTrialTestCourse : public AActor
{
    GENERATED_BODY()
    
public:    
    ATimeTrialTestCourse();

protected:
    virtual void BeginPlay() override;

public:    
    // === COURSE CONFIGURATION ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time Trial Course")
    float CourseRadius = 2000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time Trial Course")
    int32 NumberOfCheckpoints = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time Trial Course")
    float CheckpointHeight = 50.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time Trial Course")
    float TimeLimit = 90.f; // 90 seconds for the course

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time Trial Course")
    bool bAutoStartOnPlay = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time Trial Course")
    bool bShowDebugVisuals = true;

private:
    UPROPERTY()
    ACheckpointSystem* CheckpointSystem;

    UPROPERTY()
    TArray<ACheckpoint*> Checkpoints;

    void SpawnCheckpoints();
    void SetupCheckpointSystem();
};