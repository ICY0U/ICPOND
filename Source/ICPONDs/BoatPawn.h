#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/TimelineComponent.h"
#include "CheckpointSystemInterface.h"
#include "BoatPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UParticleSystemComponent;
class UAudioComponent;
class ACheckpointSystem;
class ACheckpoint;

UENUM(BlueprintType)
enum class EBoatTrickType : uint8
{
    None,
    Barrel_Roll,
    Front_Flip,
    Back_Flip,
    Spin_360,
    Perfect_Landing
};

USTRUCT(BlueprintType)
struct FBoatTrick
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    EBoatTrickType TrickType = EBoatTrickType::None;

    UPROPERTY(BlueprintReadOnly)
    int32 Points = 0;

    UPROPERTY(BlueprintReadOnly)
    FString TrickName = TEXT("");

    FBoatTrick()
    {
        TrickType = EBoatTrickType::None;
        Points = 0;
        TrickName = TEXT("");
    }

    FBoatTrick(EBoatTrickType Type, int32 Pts, const FString& Name)
    {
        TrickType = Type;
        Points = Pts;
        TrickName = Name;
    }
};

UCLASS()
class ICPONDS_API ABoatPawn : public APawn, public ICheckpointSystemInterface
{
    GENERATED_BODY()

public:
    ABoatPawn();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Function to update water level from WaterManager
    UFUNCTION(BlueprintCallable, Category="Boat|Water")
    void SetWaterLevel(float NewWaterLevel) { WaterLevel = NewWaterLevel; }

    // Emergency function to reset boat position above water
    UFUNCTION(BlueprintCallable, Category="Boat|Debug")
    void ResetBoatPosition()
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Z = 100.f; // Place 1 meter above water
        SetActorLocation(NewLocation);
        
        // Reset physics velocity
        if (BoatMesh)
        {
            BoatMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
            BoatMesh->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Boat position reset to Z: %.1f"), NewLocation.Z);
    }

    // Arcade Features - Public Access
    UFUNCTION(BlueprintCallable, Category="Boat|Arcade")
    void ActivateBoost();

    UFUNCTION(BlueprintCallable, Category="Boat|Arcade")
    void PerformJump();

    UFUNCTION(BlueprintCallable, Category="Boat|Arcade")
    int32 GetCurrentScore() const { return CurrentScore; }

    UFUNCTION(BlueprintCallable, Category="Boat|Arcade")
    float GetBoostEnergy() const { return BoostEnergy; }

    UFUNCTION(BlueprintCallable, Category="Boat|Arcade")
    bool IsInAir() const { return bIsInAir; }

    // === TIME TRIAL SYSTEM ===
    UPROPERTY(EditAnywhere, Category="Boat|Time Trial")
    bool bTimeTrialMode = false; // Toggle time trial mode

    UPROPERTY(EditAnywhere, Category="Boat|Time Trial")
    float TimeTrialDuration = 60.f; // Default 1 minute trial

    UPROPERTY(EditAnywhere, Category="Boat|Time Trial")
    bool bTimeTrialActive = false; // Is a trial currently running

    UPROPERTY(EditAnywhere, Category="Boat|Time Trial")
    float TimeTrialTimeRemaining = 0.f; // Seconds left in current trial

    UPROPERTY(EditAnywhere, Category="Boat|Time Trial")
    int32 TimeTrialBestScore = 0; // Best score achieved in time trials

    UPROPERTY(EditAnywhere, Category="Boat|Time Trial")
    float TimeTrialBestTime = 0.f; // Best time for completing objectives

    UPROPERTY(EditAnywhere, Category="Boat|Time Trial")
    int32 TimeTrialCurrentScore = 0; // Score for current trial

    UPROPERTY(EditAnywhere, Category="Boat|Time Trial")
    float TimeTrialScoreMultiplier = 1.5f; // Score multiplier during time trials

    // === TIME TRIAL PUBLIC FUNCTIONS ===
    UFUNCTION(BlueprintCallable, Category="Boat|Time Trial")
    void StartTimeTrial(float Duration = 60.f);

    UFUNCTION(BlueprintCallable, Category="Boat|Time Trial")
    void EndTimeTrial();

    UFUNCTION(BlueprintCallable, Category="Boat|Time Trial")
    bool IsTimeTrialActive() const { return bTimeTrialActive; }

    UFUNCTION(BlueprintCallable, Category="Boat|Time Trial")
    float GetTimeTrialTimeRemaining() const { return TimeTrialTimeRemaining; }

    UFUNCTION(BlueprintCallable, Category="Boat|Time Trial")
    int32 GetTimeTrialCurrentScore() const { return TimeTrialCurrentScore; }

    UFUNCTION(BlueprintCallable, Category="Boat|Time Trial")
    int32 GetTimeTrialBestScore() const { return TimeTrialBestScore; }

    // === CHECKPOINT SYSTEM INTEGRATION ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boat|Checkpoint")
    ACheckpointSystem* CurrentCheckpointSystem = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boat|Checkpoint")
    bool bAutoJoinCheckpointRaces = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boat|Checkpoint")
    int32 CheckpointBonusMultiplier = 2; // Multiplier for checkpoint bonuses in time trials

    // === CHECKPOINT SYSTEM FUNCTIONS ===
    UFUNCTION(BlueprintCallable, Category="Boat|Checkpoint")
    void JoinCheckpointSystem(ACheckpointSystem* CheckpointSystem);

    UFUNCTION(BlueprintCallable, Category="Boat|Checkpoint")
    void LeaveCheckpointSystem();

    UFUNCTION(BlueprintCallable, Category="Boat|Checkpoint")
    void StartCheckpointRace();

    // === CHECKPOINT INTERFACE IMPLEMENTATIONS ===
    virtual void NotifyCheckpointRaceStarted(ACheckpointSystem* CheckpointSystem) override;
    virtual void NotifyCheckpointRaceEnded(ACheckpointSystem* CheckpointSystem, bool bCompleted, float TotalTime, int32 FinalScore) override;
    virtual void NotifyCheckpointCompleted(ACheckpoint* Checkpoint, int32 CheckpointNumber, float CompletionTime) override;
    virtual void NotifyCheckpointBonus(ACheckpoint* Checkpoint, float BonusPoints, float BonusTime) override;

protected:
    virtual void BeginPlay() override;

private:
    // Boat Components
    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* BoatMesh; // Your custom boat mesh

    UPROPERTY(VisibleAnywhere, Category="Components")
    USpringArmComponent* SpringArm; // Camera boom for third-person view

    UPROPERTY(VisibleAnywhere, Category="Components")
    UCameraComponent* Camera; // Third-person camera

    // Arcade Effect Components
    UPROPERTY(VisibleAnywhere, Category="Components|Arcade")
    UParticleSystemComponent* BoostParticles;

    UPROPERTY(VisibleAnywhere, Category="Components|Arcade")
    UParticleSystemComponent* WakeParticles;

    UPROPERTY(VisibleAnywhere, Category="Components|Arcade")
    UParticleSystemComponent* SplashParticles;

    UPROPERTY(VisibleAnywhere, Category="Components|Arcade")
    UAudioComponent* EngineAudio;

    // Movement System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float MaxThrust = 45000.f; // Forward/backward thrust force

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float TurnTorque = 150000.f; // Turning force

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float MaxSpeed = 1200.f; // Maximum boat speed (cm/s)

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float MinTurnSpeed = 200.f; // Minimum speed needed for effective turning

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float TurnSpeedMultiplier = 1.5f; // How much speed affects turn rate

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    bool bUseSpeedBasedTurning = true; // Turn better at higher speeds

    // Arcade Movement Properties
    UPROPERTY(EditAnywhere, Category="Boat|Arcade Movement")
    float ArcadeMaxSpeed = 3000.f; // Much faster arcade speed

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Movement")
    float ArcadeAcceleration = 2.5f; // Snappier acceleration

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Movement")
    float ArcadeTurnSpeed = 3.0f; // Faster turning

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Movement")
    bool bArcadeMode = true; // Toggle arcade vs realistic physics

    // Boost System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Arcade Boost")
    float MaxBoostEnergy = 100.f;

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Boost")
    float BoostRegenRate = 15.f; // Energy per second

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Boost")
    float BoostConsumptionRate = 35.f; // Energy per second when boosting

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Boost")
    float BoostMultiplier = 2.5f; // Speed multiplier during boost

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Boost")
    float BoostMinimumEnergy = 20.f; // Minimum energy to start boost

    // Jump System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Arcade Jump")
    float JumpForce = 80000.f; // Upward force for jumping

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Jump")
    float MinJumpSpeed = 800.f; // Minimum speed required to jump

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Jump")
    float JumpCooldown = 2.f; // Seconds between jumps

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Jump")
    float AirControlMultiplier = 0.7f; // Movement control while airborne

    // Trick System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Arcade Tricks")
    float MinAirTimeForTricks = 0.5f; // Minimum air time to register tricks

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Tricks")
    float TrickDetectionSensitivity = 45.f; // Degrees for trick detection

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Tricks")
    float PerfectLandingAngle = 15.f; // Max angle deviation for perfect landing

    // Score System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Arcade Score")
    int32 SpeedBonusThreshold = 2000; // Speed for bonus points

    UPROPERTY(EditAnywhere, Category="Boat|Arcade Score")
    int32 SpeedBonusPoints = 10; // Points per second at high speed

    // Camera System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float CameraShakeIntensity = 1.f; // How much camera shakes during movement

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float CameraFollowSpeed = 3.f; // How smoothly camera follows boat movement

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float MouseSensitivityX = 1.f; // Horizontal mouse sensitivity

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float MouseSensitivityY = 0.7f; // Vertical mouse sensitivity

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float MinPitchAngle = -80.f; // Maximum upward camera angle

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float MaxPitchAngle = 10.f; // Maximum downward camera angle

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    bool bEnableMouseControl = true; // Toggle mouse camera control

    // Arcade Camera Properties
    UPROPERTY(EditAnywhere, Category="Boat|Camera Arcade")
    float BoostCameraFOV = 85.f; // Wider FOV during boost

    UPROPERTY(EditAnywhere, Category="Boat|Camera Arcade")
    float NormalCameraFOV = 70.f; // Normal FOV

    UPROPERTY(EditAnywhere, Category="Boat|Camera Arcade")
    float AirCameraDistance = 800.f; // Camera distance when airborne

    UPROPERTY(EditAnywhere, Category="Boat|Camera Arcade")
    float SpeedCameraShake = 3.f; // Extra shake at high speeds

    // Enhanced Water Physics
    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float WaterLevel = 0.f;

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float BuoyancyForce = 50000.f; // Increased for stronger floating

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float WaterDensity = 1.2f;

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float SubmersionDepth = 80.f; // Reduced for more responsive buoyancy

    // Arcade State Variables
    float BoostEnergy = 100.f;
    bool bIsBoosting = false;
    bool bIsInAir = false;
    float AirTime = 0.f;
    float LastJumpTime = 0.f;
    int32 CurrentScore = 0;
    float SpeedBonusTimer = 0.f;
    float LastSpeedBonusTime = 0.f;

    // Trick Detection Variables
    FRotator AirStartRotation = FRotator::ZeroRotator;
    FRotator MaxAirRotation = FRotator::ZeroRotator;
    bool bTrickInProgress = false;
    TArray<FBoatTrick> PerformedTricks;

    // Timer handles for effects
    FTimerHandle SplashEffectTimerHandle;
    FTimerHandle LandingEffectTimerHandle;

    // Movement state variables
    float ThrottleInput = 0.f;
    float SteeringInput = 0.f;
    float CameraYawInput = 0.f; // Mouse X input accumulation
    float CameraPitchInput = 0.f; // Mouse Y input accumulation
    float LastDebugTime = 0.f; // For debug logging

    // Input functions
    void MoveForward(float Value);
    void MoveRight(float Value);
    void MouseX(float Value);
    void MouseY(float Value);

    // Arcade Input Functions
    void StartBoost();
    void StopBoost();
    void Jump();
    void TrickLeft();
    void TrickRight();

    // === TIME TRIAL INPUT FUNCTIONS ===
    void StartTimeTrialInput();
    void EndTimeTrialInput();

    // Physics functions
    void ApplyWaterDrag(float DeltaTime);
    void ApplyBuoyancy(float DeltaTime);
    void UpdateCameraDynamics(float DeltaTime);

    // Arcade Physics Functions
    void UpdateArcadeMovement(float DeltaTime);
    void UpdateBoostSystem(float DeltaTime);
    void UpdateJumpSystem(float DeltaTime);
    void UpdateTrickSystem(float DeltaTime);
    void UpdateScoreSystem(float DeltaTime);
    void UpdateArcadeEffects(float DeltaTime);

    // Arcade Helper Functions
    void CheckTrickCompletion();
    void AddScore(int32 Points, const FString& Reason = TEXT(""));
    void ShowTrickFeedback(const FBoatTrick& Trick);
    void PlayBoostEffects(bool bStart);
    void PlayJumpEffects();
    void PlayLandingEffects(bool bPerfectLanding);
    float CalculateCurrentMaxSpeed() const;
    bool CanJump() const;
    FBoatTrick DetectTrickFromRotation(const FRotator& StartRot, const FRotator& EndRot) const;

    // === TIME TRIAL HELPER FUNCTIONS ===
    void UpdateTimeTrialSystem(float DeltaTime);
    void ShowTimeTrialUI();
    void OnTimeTrialScoreAdded(int32 Points, const FString& Reason);
};
