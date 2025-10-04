#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Checkpoint.generated.h"

UENUM(BlueprintType)
enum class ECheckpointState : uint8
{
    Inactive,
    Active,
    Completed
};

UENUM(BlueprintType)
enum class ECheckpointType : uint8
{
    Standard,       // Regular checkpoint
    Start,          // Starting line
    Finish,         // Finish line
    Bonus,          // Optional bonus checkpoint
    TimeBonus       // Adds extra time when collected
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCheckpointTriggered, class ACheckpoint*, Checkpoint, AActor*, TriggeringActor, float, CompletionTime);

UCLASS()
class ICPONDS_API ACheckpoint : public AActor
{
    GENERATED_BODY()
    
public:    
    ACheckpoint();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    // === CHECKPOINT PROPERTIES ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint")
    ECheckpointType CheckpointType = ECheckpointType::Standard;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint")
    ECheckpointState CheckpointState = ECheckpointState::Inactive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint")
    int32 CheckpointID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint")
    FString CheckpointName = TEXT("Checkpoint");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint")
    bool bIsOptional = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint")
    float BonusPoints = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint")
    float BonusTime = 0.f; // Extra time awarded (for time trial checkpoints)

    // === VISUAL PROPERTIES ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint|Visual")
    FLinearColor InactiveColor = FLinearColor::Gray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint|Visual")
    FLinearColor ActiveColor = FLinearColor::Green;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint|Visual")
    FLinearColor CompletedColor = FLinearColor::Blue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint|Visual")
    float PulseSpeed = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint|Visual")
    float PulseIntensity = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint|Visual")
    bool bShowDebugInfo = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint|Visual")
    bool bShowDebugSphere = true;

    // === DETECTION PROPERTIES ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint|Detection")
    float TriggerRadius = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Checkpoint|Detection")
    TArray<TSubclassOf<AActor>> ValidTriggerClasses;

    // === EVENTS ===
    UPROPERTY(BlueprintAssignable, Category="Checkpoint|Events")
    FOnCheckpointTriggered OnCheckpointTriggered;

    // === PUBLIC FUNCTIONS ===
    UFUNCTION(BlueprintCallable, Category="Checkpoint")
    void ActivateCheckpoint();

    UFUNCTION(BlueprintCallable, Category="Checkpoint")
    void DeactivateCheckpoint();

    UFUNCTION(BlueprintCallable, Category="Checkpoint")
    void CompleteCheckpoint(AActor* TriggeringActor, float CompletionTime = 0.f);

    UFUNCTION(BlueprintCallable, Category="Checkpoint")
    void ResetCheckpoint();

    UFUNCTION(BlueprintPure, Category="Checkpoint")
    bool IsActive() const { return CheckpointState == ECheckpointState::Active; }

    UFUNCTION(BlueprintPure, Category="Checkpoint")
    bool IsCompleted() const { return CheckpointState == ECheckpointState::Completed; }

    UFUNCTION(BlueprintPure, Category="Checkpoint")
    bool CanTrigger(AActor* Actor) const;

protected:
    // === COMPONENTS ===
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UStaticMeshComponent* CheckpointMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USphereComponent* TriggerSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UParticleSystemComponent* ParticleEffect;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UAudioComponent* AudioComponent;

    // === OVERLAP EVENTS ===
    UFUNCTION()
    void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    // === INTERNAL FUNCTIONS ===
    void UpdateVisualState();
    void UpdateParticleEffects();
    void PlayTriggerEffects();

private:
    // === STATE VARIABLES ===
    float TimeCreated = 0.f;
    bool bActorInTrigger = false;
    AActor* CurrentTriggeringActor = nullptr;
};