#include "BoatPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/PlayerInput.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "CheckpointSystem.h"
#include "Checkpoint.h"

ABoatPawn::ABoatPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Main boat mesh - use your custom boat mesh
    BoatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoatMesh"));
    SetRootComponent(BoatMesh);
    BoatMesh->SetSimulatePhysics(true);
    BoatMesh->SetLinearDamping(0.1f); // Low damping for smooth movement
    BoatMesh->SetAngularDamping(2.5f); // Moderate angular damping for realistic turning
    BoatMesh->SetEnableGravity(true);
    BoatMesh->BodyInstance.bUseCCD = true;
    BoatMesh->SetMassOverrideInKg(NAME_None, 200.f); // Boat mass
    
    // FIXED: Custom collision to prevent flipping on ramps/planes
    BoatMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoatMesh->SetCollisionObjectType(ECC_Pawn); // Set as Pawn for triggers to detect
    
    // Set collision responses
    BoatMesh->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignore everything by default
    BoatMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap); // OVERLAP with static geometry (ramps, planes)
    BoatMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block); // Block dynamic objects
    BoatMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Overlap with other pawns (triggers, checkpoints)
    BoatMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block); // Block physics objects
    BoatMesh->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Block); // Block vehicles
    BoatMesh->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block); // Block destructibles

    // Load your custom boat mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CustomBoatMeshObj(TEXT("/Game/Boat/Boat/StaticMeshes/Boat"));
    if (CustomBoatMeshObj.Succeeded())
    {
        BoatMesh->SetStaticMesh(CustomBoatMeshObj.Object);
        // Scale up the boat (no rotation needed since you fixed it in Blender)
        BoatMesh->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f)); // Make it 50% bigger
    }
    else
    {
        // Fallback to basic shape if custom mesh fails to load
        static ConstructorHelpers::FObjectFinder<UStaticMesh> FallbackMeshObj(TEXT("/Engine/BasicShapes/Cube.Cube"));
        if (FallbackMeshObj.Succeeded())
        {
            BoatMesh->SetStaticMesh(FallbackMeshObj.Object);
            BoatMesh->SetWorldScale3D(FVector(5.0f, 2.0f, 0.8f));
        }
        UE_LOG(LogTemp, Warning, TEXT("Failed to load custom boat mesh, using fallback"));
    }

    // Camera setup for cinematic third-person experience
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(BoatMesh);
    SpringArm->TargetArmLength = 600.f; // Distance from boat
    SpringArm->bDoCollisionTest = true; // Enable collision to avoid clipping
    SpringArm->bUsePawnControlRotation = false; // Fixed camera angle
    SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f)); // Downward angle to see boat
    SpringArm->SetRelativeLocation(FVector(-100.f, 0.f, 80.f)); // Behind and above boat
    SpringArm->SocketOffset = FVector(0.f, 0.f, 20.f); // Raise camera slightly

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->SetFieldOfView(NormalCameraFOV); // Wide FOV to see the boat

    // === ARCADE EFFECT COMPONENTS ===
    
    // Boost Particles - Attached to back of boat
    BoostParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BoostParticles"));
    BoostParticles->SetupAttachment(BoatMesh);
    BoostParticles->SetRelativeLocation(FVector(-250.f, 0.f, 0.f)); // Behind boat
    BoostParticles->bAutoActivate = false;
    
    // Try to load boost particle effect
    static ConstructorHelpers::FObjectFinder<UParticleSystem> BoostFX(TEXT("/Engine/VFX/P_Fire"));
    if (BoostFX.Succeeded())
    {
        BoostParticles->SetTemplate(BoostFX.Object);
    }

    // Wake Particles - Water spray behind boat
    WakeParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WakeParticles"));
    WakeParticles->SetupAttachment(BoatMesh);
    WakeParticles->SetRelativeLocation(FVector(-150.f, 0.f, -40.f)); // Behind and below boat
    WakeParticles->bAutoActivate = true;
    
    // Try to load wake particle effect
    static ConstructorHelpers::FObjectFinder<UParticleSystem> WakeFX(TEXT("/Engine/VFX/P_Steam_Lit"));
    if (WakeFX.Succeeded())
    {
        WakeParticles->SetTemplate(WakeFX.Object);
    }

    // Splash Particles - For jumps and landings
    SplashParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SplashParticles"));
    SplashParticles->SetupAttachment(BoatMesh);
    SplashParticles->SetRelativeLocation(FVector(0.f, 0.f, -50.f)); // Below boat
    SplashParticles->bAutoActivate = false;
    
    // Try to load splash particle effect
    static ConstructorHelpers::FObjectFinder<UParticleSystem> SplashFX(TEXT("/Engine/VFX/P_Explosion"));
    if (SplashFX.Succeeded())
    {
        SplashParticles->SetTemplate(SplashFX.Object);
    }

    // Engine Audio Component
    EngineAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineAudio"));
    EngineAudio->SetupAttachment(BoatMesh);
    EngineAudio->bAutoActivate = true;
    
    // Try to load engine sound
    static ConstructorHelpers::FObjectFinder<USoundCue> EngineSoundCue(TEXT("/Engine/EditorSounds/Notifications/CompileSuccess_Cue"));
    if (EngineSoundCue.Succeeded())
    {
        EngineAudio->SetSound(EngineSoundCue.Object);
        EngineAudio->SetVolumeMultiplier(0.3f);
    }

    AutoPossessPlayer = EAutoReceiveInput::Player0;
    
    // Initialize arcade values
    BoostEnergy = MaxBoostEnergy;
    CurrentScore = 0;
    bIsBoosting = false;
    bIsInAir = false;
    AirTime = 0.f;
    LastJumpTime = -JumpCooldown; // Allow immediate first jump
}

void ABoatPawn::BeginPlay()
{
    Super::BeginPlay();
    
    // Make sure boat spawns above water level
    FVector CurrentLocation = GetActorLocation();
    if (CurrentLocation.Z < 50.f) // If spawning below 50cm above origin
    {
        CurrentLocation.Z = 50.f; // Place 50cm above water level
        SetActorLocation(CurrentLocation);
        UE_LOG(LogTemp, Warning, TEXT("?? ARCADE BOAT READY! Position: Z: %.1f"), CurrentLocation.Z);
    }
    
    // Initialize water level to 0 as default
    WaterLevel = 0.f;
    
    // Display arcade mode status
    if (bArcadeMode)
    {
        UE_LOG(LogTemp, Warning, TEXT("?? ARCADE MODE ACTIVATED! Boost Ready, Max Speed: %.0f cm/s"), ArcadeMaxSpeed);
    }
}

void ABoatPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (BoatMesh && BoatMesh->IsSimulatingPhysics())
    {
        // SAFETY CHECK: If boat falls way below water, teleport it back up
        const FVector CurrentLocation = GetActorLocation();
        if (CurrentLocation.Z < (WaterLevel - 100.f)) // Reduced threshold - if more than 1m below water
        {
            FVector SafeLocation = CurrentLocation;
            SafeLocation.Z = WaterLevel + 50.f; // Place 50cm above water
            SetActorLocation(SafeLocation);
            
            // Reset all velocities
            BoatMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
            BoatMesh->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);
            
            UE_LOG(LogTemp, Error, TEXT("?? EMERGENCY TELEPORT - Arcade boat was at Z: %.1f, moved to Z: %.1f"), 
                CurrentLocation.Z, SafeLocation.Z);
        }
        
        // Apply water physics
        ApplyBuoyancy(DeltaTime);
        ApplyWaterDrag(DeltaTime);

        // === ARCADE SYSTEMS UPDATE ===
        if (bArcadeMode)
        {
            UpdateArcadeMovement(DeltaTime);
            UpdateBoostSystem(DeltaTime);
            UpdateJumpSystem(DeltaTime);
            UpdateTrickSystem(DeltaTime);
            UpdateScoreSystem(DeltaTime);
            UpdateArcadeEffects(DeltaTime);
            
            // === TIME TRIAL SYSTEM UPDATE ===
            if (bTimeTrialMode)
            {
                UpdateTimeTrialSystem(DeltaTime);
            }
        }
        else
        {
            // Original realistic movement
            const FVector Forward = GetActorForwardVector();
            const FVector Force = Forward * (ThrottleInput * MaxThrust);
            BoatMesh->AddForce(Force);

            // Apply turning torque
            const FVector Torque = FVector(0.f, 0.f, SteeringInput * TurnTorque);
            BoatMesh->AddTorqueInRadians(Torque);

            // Cap speed
            const FVector Vel = BoatMesh->GetPhysicsLinearVelocity();
            const float Speed = Vel.Size();
            if (Speed > MaxSpeed)
            {
                const FVector Clamped = Vel.GetSafeNormal() * MaxSpeed;
                BoatMesh->SetPhysicsLinearVelocity(Clamped);
            }
        }

        // Update camera dynamics for cinematic feel
        UpdateCameraDynamics(DeltaTime);

        // Debug display every second
        const float CurrentTime = GetWorld()->GetTimeSeconds();
        if (CurrentTime - LastDebugTime > 1.0f)
        {
            LastDebugTime = CurrentTime;
            const FVector Vel = BoatMesh->GetPhysicsLinearVelocity();
            const float Speed = Vel.Size();
            
            if (bArcadeMode)
            {
                FString ArcadeDebug = FString::Printf(
                    TEXT("?? ARCADE MODE | Speed: %.0f | Boost: %.0f%% | Score: %d | %s"), 
                    Speed, 
                    (BoostEnergy / MaxBoostEnergy) * 100.f, 
                    CurrentScore,
                    bIsInAir ? TEXT("AIRBORNE!") : TEXT("On Water")
                );
                GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Cyan, ArcadeDebug);
                
                if (bIsBoosting)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Yellow, TEXT("?? BOOST ACTIVE!"));
                }
            }
            else
            {
                FString MoveDebug = FString::Printf(TEXT("Throttle: %.2f | Steering: %.2f | Speed: %.1f cm/s"), 
                    ThrottleInput, SteeringInput, Speed);
                GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, MoveDebug);
            }
        }
    }
}

// === ARCADE MOVEMENT SYSTEM ===
void ABoatPawn::UpdateArcadeMovement(float DeltaTime)
{
    const FVector Forward = GetActorForwardVector();
    const FVector Right = GetActorRightVector();
    
    // Calculate target forces with arcade responsiveness
    float CurrentMaxSpeed = CalculateCurrentMaxSpeed();
    float ArcadeThrust = MaxThrust * ArcadeAcceleration;
    float ArcadeTorqueForce = TurnTorque * ArcadeTurnSpeed;
    
    // Get current speed for turn calculations
    const FVector Vel = BoatMesh->GetPhysicsLinearVelocity();
    const float Speed = Vel.Size();
    
    // Apply forward/backward force
    if (FMath::Abs(ThrottleInput) > 0.1f)
    {
        FVector ThrustForce = Forward * (ThrottleInput * ArcadeThrust);
        
        // Reduce control while airborne
        if (bIsInAir)
        {
            ThrustForce *= AirControlMultiplier;
        }
        
        BoatMesh->AddForce(ThrustForce);
    }

    // Apply turning force with IMPROVED speed-based responsiveness
    if (FMath::Abs(SteeringInput) > 0.1f)
    {
        // Calculate turn effectiveness based on speed
        float TurnEffectiveness = 1.f;
        
        if (bUseSpeedBasedTurning && !bIsInAir)
        {
            // Boats turn better at speed
            if (Speed < MinTurnSpeed)
            {
                // Very slow - poor turning
                TurnEffectiveness = 0.3f;
            }
            else
            {
                // Speed-based turn boost (faster = better turning)
                float SpeedRatio = FMath::Clamp(Speed / CurrentMaxSpeed, 0.f, 1.f);
                TurnEffectiveness = 0.5f + (SpeedRatio * TurnSpeedMultiplier);
            }
        }
        
        FVector TurnForceVector = FVector(0.f, 0.f, SteeringInput * ArcadeTorqueForce * TurnEffectiveness);
        
        // Enhanced turning while airborne for tricks
        if (bIsInAir)
        {
            TurnForceVector *= 1.5f;
        }
        
        BoatMesh->AddTorqueInRadians(TurnForceVector);
        
        // ADDED: Apply lateral force for more responsive turning (like a rudder)
        if (!bIsInAir && Speed > MinTurnSpeed)
        {
            float LateralForce = SteeringInput * Speed * 30.f * TurnEffectiveness;
            FVector TurnAssist = Right * LateralForce;
            BoatMesh->AddForce(TurnAssist);
        }
    }

    // Cap speed to current maximum
    if (Speed > CurrentMaxSpeed)
    {
        const FVector Clamped = Vel.GetSafeNormal() * CurrentMaxSpeed;
        BoatMesh->SetPhysicsLinearVelocity(Clamped);
    }
}

// === BOOST SYSTEM ===
void ABoatPawn::UpdateBoostSystem(float DeltaTime)
{
    if (bIsBoosting && BoostEnergy > 0.f)
    {
        // Consume boost energy
        BoostEnergy = FMath::Max(0.f, BoostEnergy - (BoostConsumptionRate * DeltaTime));
        
        // If energy depleted, stop boost
        if (BoostEnergy <= 0.f)
        {
            StopBoost();
        }
    }
    else if (!bIsBoosting && BoostEnergy < MaxBoostEnergy)
    {
        // Regenerate boost energy
        BoostEnergy = FMath::Min(MaxBoostEnergy, BoostEnergy + (BoostRegenRate * DeltaTime));
    }
}

// === JUMP SYSTEM ===
void ABoatPawn::UpdateJumpSystem(float DeltaTime)
{
    const FVector CurrentLocation = GetActorLocation();
    const bool WasInAir = bIsInAir;
    
    // IMPROVED: Check if we're in the air with better detection
    // Consider both height above water AND vertical velocity
    float HeightAboveWater = CurrentLocation.Z - WaterLevel;
    FVector CurrentVelocity = BoatMesh->GetPhysicsLinearVelocity();
    
    // In air if: significantly above water OR moving upward fast
    bIsInAir = (HeightAboveWater > 50.f) || (HeightAboveWater > 20.f && CurrentVelocity.Z > 50.f);
    
    if (bIsInAir)
    {
        AirTime += DeltaTime;
        
        // Start trick detection if we just became airborne
        if (!WasInAir)
        {
            AirStartRotation = GetActorRotation();
            MaxAirRotation = AirStartRotation;
            bTrickInProgress = true;
            
            PlayJumpEffects();
            UE_LOG(LogTemp, Warning, TEXT("?? AIRBORNE! Air time starting... Height: %.1f"), HeightAboveWater);
        }
    }
    else if (WasInAir)
    {
        // Just landed
        const bool bPerfectLanding = FMath::Abs(GetActorRotation().Pitch) < PerfectLandingAngle && 
                                   FMath::Abs(GetActorRotation().Roll) < PerfectLandingAngle;
        
        PlayLandingEffects(bPerfectLanding);
        
        if (bPerfectLanding && AirTime > MinAirTimeForTricks)
        {
            AddScore(50, TEXT("Perfect Landing!"));
        }
        
        // Check for completed tricks
        if (bTrickInProgress && AirTime > MinAirTimeForTricks)
        {
            CheckTrickCompletion();
        }
        
        UE_LOG(LogTemp, Warning, TEXT("?? SPLASH LANDING! Air time: %.2f seconds"), AirTime);
        
        // Reset air tracking
        AirTime = 0.f;
        bTrickInProgress = false;
    }
}

// === TRICK SYSTEM ===
void ABoatPawn::UpdateTrickSystem(float DeltaTime)
{
    if (bIsInAir && bTrickInProgress)
    {
        const FRotator CurrentRotation = GetActorRotation();
        
        // Track maximum rotation achieved during air time
        if (FMath::Abs(CurrentRotation.Pitch) > FMath::Abs(MaxAirRotation.Pitch))
        {
            MaxAirRotation.Pitch = CurrentRotation.Pitch;
        }
        if (FMath::Abs(CurrentRotation.Roll) > FMath::Abs(MaxAirRotation.Roll))
        {
            MaxAirRotation.Roll = CurrentRotation.Roll;
        }
        if (FMath::Abs(CurrentRotation.Yaw - AirStartRotation.Yaw) > FMath::Abs(MaxAirRotation.Yaw - AirStartRotation.Yaw))
        {
            MaxAirRotation.Yaw = CurrentRotation.Yaw;
        }
    }
}

// === SCORE SYSTEM ===
void ABoatPawn::UpdateScoreSystem(float DeltaTime)
{
    const FVector Vel = BoatMesh->GetPhysicsLinearVelocity();
    const float Speed = Vel.Size();
    
    // Speed bonus points
    if (Speed > SpeedBonusThreshold)
    {
        SpeedBonusTimer += DeltaTime;
        if (SpeedBonusTimer >= 1.f) // Every second at high speed
        {
            AddScore(SpeedBonusPoints, TEXT("Speed Bonus!"));
            SpeedBonusTimer = 0.f;
        }
    }
    else
    {
        SpeedBonusTimer = 0.f;
    }
}

// === VISUAL EFFECTS ===
void ABoatPawn::UpdateArcadeEffects(float DeltaTime)
{
    const FVector Vel = BoatMesh->GetPhysicsLinearVelocity();
    const float Speed = Vel.Size();
    const float SpeedRatio = Speed / ArcadeMaxSpeed;
    
    // Update engine audio pitch based on speed
    if (EngineAudio && EngineAudio->GetSound())
    {
        float PitchMultiplier = 0.8f + (SpeedRatio * 0.7f); // 0.8 to 1.5 range
        if (bIsBoosting)
        {
            PitchMultiplier += 0.3f; // Higher pitch during boost
        }
        EngineAudio->SetPitchMultiplier(PitchMultiplier);
        EngineAudio->SetVolumeMultiplier(0.3f + (SpeedRatio * 0.4f)); // Volume scales with speed
    }
    
    // Update wake particles based on speed
    if (WakeParticles && !bIsInAir)
    {
        WakeParticles->SetFloatParameter(TEXT("SpeedMultiplier"), SpeedRatio);
    }
}

// === ARCADE INPUT FUNCTIONS ===
void ABoatPawn::StartBoost()
{
    if (BoostEnergy >= BoostMinimumEnergy && !bIsBoosting)
    {
        bIsBoosting = true;
        PlayBoostEffects(true);
        AddScore(5, TEXT("Boost Started!"));
        UE_LOG(LogTemp, Warning, TEXT("?? BOOST ACTIVATED! Energy: %.1f"), BoostEnergy);
    }
}

void ABoatPawn::StopBoost()
{
    if (bIsBoosting)
    {
        bIsBoosting = false;
        PlayBoostEffects(false);
        UE_LOG(LogTemp, Warning, TEXT("?? Boost ended. Energy: %.1f"), BoostEnergy);
    }
}

void ABoatPawn::Jump()
{
    if (CanJump())
    {
        const FVector JumpImpulse = FVector(0.f, 0.f, JumpForce);
        BoatMesh->AddImpulse(JumpImpulse);
        LastJumpTime = GetWorld()->GetTimeSeconds();
        AddScore(25, TEXT("Jump!"));
        UE_LOG(LogTemp, Warning, TEXT("?? JUMP INITIATED! Force: %.0f"), JumpForce);
    }
}

void ABoatPawn::TrickLeft()
{
    if (bIsInAir)
    {
        const FVector TrickTorque = FVector(0.f, -50000.f, 0.f); // Roll left
        BoatMesh->AddTorqueInRadians(TrickTorque);
        UE_LOG(LogTemp, Log, TEXT("?? Left trick input during air time"));
    }
}

void ABoatPawn::TrickRight()
{
    if (bIsInAir)
    {
        const FVector TrickTorque = FVector(0.f, 50000.f, 0.f); // Roll right
        BoatMesh->AddTorqueInRadians(TrickTorque);
        UE_LOG(LogTemp, Log, TEXT("?? Right trick input during air time"));
    }
}

// === TIME TRIAL INPUT FUNCTIONS ===
void ABoatPawn::StartTimeTrialInput()
{
    if (!bTimeTrialActive)
    {
        // Start with default duration, can be customized later
        bTimeTrialMode = true;
        StartTimeTrial(TimeTrialDuration);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("?? Time Trial already running! Press End key to stop."));
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("?? Time Trial already running!"));
        }
    }
}

void ABoatPawn::EndTimeTrialInput()
{
    if (bTimeTrialActive)
    {
        EndTimeTrial();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("?? No active Time Trial to end."));
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("?? No active Time Trial to end."));
        }
    }
}

// === PUBLIC ARCADE FUNCTIONS ===
void ABoatPawn::ActivateBoost()
{
    StartBoost();
}

void ABoatPawn::PerformJump()
{
    Jump();
}

// === HELPER FUNCTIONS ===
float ABoatPawn::CalculateCurrentMaxSpeed() const
{
    float CurrentMaxSpeed = bArcadeMode ? ArcadeMaxSpeed : MaxSpeed;
    
    if (bIsBoosting)
    {
        CurrentMaxSpeed *= BoostMultiplier;
    }
    
    return CurrentMaxSpeed;
}

bool ABoatPawn::CanJump() const
{
    const FVector Vel = BoatMesh->GetPhysicsLinearVelocity();
    const float Speed = Vel.Size();
    const float TimeSinceLastJump = GetWorld()->GetTimeSeconds() - LastJumpTime;
    
    // IMPROVED: Better water contact detection
    const FVector CurrentLocation = GetActorLocation();
    float HeightAboveWater = CurrentLocation.Z - WaterLevel;
    bool bOnWater = HeightAboveWater < 30.f; // More lenient
    
    // Debug output
    if (Speed >= MinJumpSpeed && TimeSinceLastJump >= JumpCooldown)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Jump Check: OnWater=%d, Speed=%.0f (need %.0f), Height=%.1f"), 
            bOnWater, Speed, MinJumpSpeed, HeightAboveWater);
    }
    
    return bOnWater && 
           Speed >= MinJumpSpeed && 
           TimeSinceLastJump >= JumpCooldown;
}

void ABoatPawn::CheckTrickCompletion()
{
    if (!bTrickInProgress) return;
    
    const FBoatTrick CompletedTrick = DetectTrickFromRotation(AirStartRotation, MaxAirRotation);
    
    if (CompletedTrick.TrickType != EBoatTrickType::None)
    {
        PerformedTricks.Add(CompletedTrick);
        AddScore(CompletedTrick.Points, CompletedTrick.TrickName);
        ShowTrickFeedback(CompletedTrick);
    }
}

FBoatTrick ABoatPawn::DetectTrickFromRotation(const FRotator& StartRot, const FRotator& EndRot) const
{
    const float PitchDiff = FMath::Abs(EndRot.Pitch - StartRot.Pitch);
    const float RollDiff = FMath::Abs(EndRot.Roll - StartRot.Roll);
    const float YawDiff = FMath::Abs(FMath::FindDeltaAngleDegrees(StartRot.Yaw, EndRot.Yaw));
    
    // Detect barrel roll (360° roll)
    if (RollDiff > 300.f && PitchDiff < 90.f)
    {
        return FBoatTrick(EBoatTrickType::Barrel_Roll, 200, TEXT("??? BARREL ROLL!"));
    }
    
    // Detect front flip
    if (PitchDiff > 300.f && EndRot.Pitch > StartRot.Pitch && RollDiff < 90.f)
    {
        return FBoatTrick(EBoatTrickType::Front_Flip, 250, TEXT("?? FRONT FLIP!"));
    }
    
    // Detect back flip
    if (PitchDiff > 300.f && EndRot.Pitch < StartRot.Pitch && RollDiff < 90.f)
    {
        return FBoatTrick(EBoatTrickType::Back_Flip, 250, TEXT("?? BACK FLIP!"));
    }
    
    // Detect 360 spin
    if (YawDiff > 300.f && PitchDiff < 90.f && RollDiff < 90.f)
    {
        return FBoatTrick(EBoatTrickType::Spin_360, 150, TEXT("?? 360 SPIN!"));
    }
    
    return FBoatTrick(); // No trick detected
}

void ABoatPawn::AddScore(int32 Points, const FString& Reason)
{
    // Add to regular score
    CurrentScore += Points;
    
    // Add to time trial score if active
    if (bTimeTrialActive)
    {
        OnTimeTrialScoreAdded(Points, Reason);
    }
    
    if (GEngine && !Reason.IsEmpty())
    {
        FString ScoreMessage = FString::Printf(TEXT("+%d - %s (Total: %d)"), Points, *Reason, CurrentScore);
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, ScoreMessage);
    }
    
    UE_LOG(LogTemp, Log, TEXT("?? SCORE +%d: %s (Total: %d)"), Points, *Reason, CurrentScore);
}

void ABoatPawn::ShowTrickFeedback(const FBoatTrick& Trick)
{
    if (GEngine)
    {
        FString TrickMessage = FString::Printf(TEXT("%s +%d Points!"), *Trick.TrickName, Trick.Points);
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Magenta, TrickMessage);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("?? TRICK COMPLETED: %s for %d points!"), *Trick.TrickName, Trick.Points);
}

void ABoatPawn::PlayBoostEffects(bool bStart)
{
    if (BoostParticles)
    {
        if (bStart)
        {
            BoostParticles->Activate();
        }
        else
        {
            BoostParticles->Deactivate();
        }
    }
}

void ABoatPawn::PlayJumpEffects()
{
    if (SplashParticles)
    {
        SplashParticles->Activate();
        
        // Auto-deactivate after short burst
        GetWorld()->GetTimerManager().SetTimer(
            SplashEffectTimerHandle,
            [this]() { 
                if (SplashParticles) 
                {
                    SplashParticles->Deactivate(); 
                }
            },
            0.5f,
            false
        );
    }
}

void ABoatPawn::PlayLandingEffects(bool bPerfectLanding)
{
    if (SplashParticles)
    {
        SplashParticles->Activate();
        
        // Auto-deactivate after splash
        GetWorld()->GetTimerManager().SetTimer(
            LandingEffectTimerHandle,
            [this]() { 
                if (SplashParticles) 
                {
                    SplashParticles->Deactivate(); 
                }
            },
            1.f,
            false
        );
    }
    
    if (bPerfectLanding && GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("? PERFECT LANDING! ?"));
    }
}

// === CAMERA DYNAMICS WITH ARCADE ENHANCEMENTS ===
void ABoatPawn::UpdateCameraDynamics(float DeltaTime)
{
    if (!SpringArm || !Camera) return;

    // Base camera position and rotation (now influenced by mouse)
    FVector BaseLocation = FVector(-100.f, 0.f, 80.f);
    FRotator BaseRotation = FRotator(-30.f + CameraPitchInput, CameraYawInput, 0.f);
    
    // === ARCADE CAMERA ENHANCEMENTS ===
    
    // Dynamic FOV based on speed and boost
    float TargetFOV = NormalCameraFOV;
    if (bIsBoosting)
    {
        TargetFOV = BoostCameraFOV;
    }
    else
    {
        const FVector Vel = BoatMesh->GetPhysicsLinearVelocity();
        const float Speed = Vel.Size();
        const float SpeedRatio = FMath::Clamp(Speed / ArcadeMaxSpeed, 0.f, 1.f);
        TargetFOV = FMath::Lerp(NormalCameraFOV, BoostCameraFOV * 0.8f, SpeedRatio);
    }
    
    float CurrentFOV = Camera->FieldOfView;
    float NewFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, 3.f);
    Camera->SetFieldOfView(NewFOV);
    
    // Dynamic camera distance when airborne
    float TargetArmLength = SpringArm->TargetArmLength;
    if (bIsInAir)
    {
        TargetArmLength = AirCameraDistance;
    }
    else
    {
        TargetArmLength = 600.f; // Normal distance
    }
    
    float NewArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, TargetArmLength, DeltaTime, 2.f);
    SpringArm->TargetArmLength = NewArmLength;
    
    // Enhanced camera shake for arcade feel
    FVector CameraShake = FVector::ZeroVector;
    float ShakeIntensity = 0.f;
    
    const FVector BoatVelocity = BoatMesh->GetPhysicsLinearVelocity();
    const float Speed = BoatVelocity.Size();
    
    // Speed-based shake
    if (Speed > 500.f)
    {
        ShakeIntensity = (Speed / ArcadeMaxSpeed) * SpeedCameraShake;
        if (bIsBoosting)
        {
            ShakeIntensity *= 1.5f; // Extra shake during boost
        }
        
        CameraShake = FVector(
            FMath::Sin(GetWorld()->GetTimeSeconds() * 12.f) * ShakeIntensity,
            FMath::Cos(GetWorld()->GetTimeSeconds() * 10.f) * ShakeIntensity * 0.7f,
            FMath::Sin(GetWorld()->GetTimeSeconds() * 15.f) * ShakeIntensity * 0.5f
        );
    }
    
    // Movement-based shake
    if (FMath::Abs(ThrottleInput) > 0.1f)
    {
        float MovementShake = FMath::Abs(ThrottleInput) * CameraShakeIntensity;
        CameraShake += FVector(
            FMath::Sin(GetWorld()->GetTimeSeconds() * 8.f) * MovementShake,
            FMath::Cos(GetWorld()->GetTimeSeconds() * 6.f) * MovementShake * 0.5f,
            FMath::Sin(GetWorld()->GetTimeSeconds() * 10.f) * MovementShake * 0.3f
        );
    }
    
    // Add velocity-based camera movement
    float VelocityInfluence = FMath::Clamp(Speed / CalculateCurrentMaxSpeed(), 0.f, 1.f);
    
    // Camera leans with turning (enhanced for arcade feel)
    FVector AngularVel = BoatMesh->GetPhysicsAngularVelocityInRadians();
    float TurnLean = AngularVel.Z * 15.f; // More pronounced lean for arcade feel
    
    // Reduced effects when mouse controlling, but still present for arcade feel
    float EffectStrength = bEnableMouseControl ? 0.5f : 1.0f;
    FVector DynamicOffset = CameraShake + FVector(
        -VelocityInfluence * 25.f * EffectStrength, // Pull back more when moving fast
        TurnLean * 3.f * EffectStrength, // More dramatic lean
        VelocityInfluence * 15.f * EffectStrength // Rise more when moving fast
    );
    
    // Extra camera effects for airborne state
    if (bIsInAir)
    {
        // Camera wobble during air time for excitement
        float AirWobble = FMath::Sin(AirTime * 3.f) * 10.f;
        DynamicOffset += FVector(0.f, AirWobble, AirWobble * 0.5f);
    }
    
    // Dynamic rotation adjustments
    FRotator DynamicRotation = BaseRotation + FRotator(
        VelocityInfluence * -8.f * EffectStrength, // Look down more when moving fast
        TurnLean * 0.8f * EffectStrength, // More yaw with turns
        TurnLean * 0.5f * EffectStrength // More roll with turns
    );
    
    // Smoothly interpolate to target position and rotation
    FVector TargetLocation = BaseLocation + DynamicOffset;
    FVector CurrentLocation = SpringArm->GetRelativeLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, CameraFollowSpeed);
    SpringArm->SetRelativeLocation(NewLocation);
    
    FRotator CurrentRotation = SpringArm->GetRelativeRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DynamicRotation, DeltaTime, CameraFollowSpeed * 2.f);
    SpringArm->SetRelativeRotation(NewRotation);
}

// === PHYSICS FUNCTIONS (Enhanced for Arcade) ===
void ABoatPawn::ApplyBuoyancy(float DeltaTime)
{
    const FVector BoatLocation = GetActorLocation();
    const float DistanceUnderWater = WaterLevel - BoatLocation.Z;
    
    // Apply buoyancy forces based on submersion
    if (DistanceUnderWater > 0.f)
    {
        // Underwater - apply upward force (reduced to prevent skipping)
        float UltraBuoyancy = bArcadeMode ? 120000.f : 100000.f; // REDUCED from 200000
        
        // Scale force with depth for stronger response
        if (DistanceUnderWater > 50.f)
        {
            UltraBuoyancy *= FMath::Min(DistanceUnderWater / 50.f, 2.f); // CAP at 2x
        }
        
        const FVector MegaBuoyancyForce = FVector(0.f, 0.f, UltraBuoyancy);
        BoatMesh->AddForce(MegaBuoyancyForce);
        
        // Counter gravity more gently
        const float GravityCounterForce = BoatMesh->GetMass() * 980.f * (bArcadeMode ? 2.5f : 2.f); // REDUCED from 4x
        BoatMesh->AddForce(FVector(0.f, 0.f, GravityCounterForce));
        
        // Limit downward velocity
        FVector CurrentVelocity = BoatMesh->GetPhysicsLinearVelocity();
        if (CurrentVelocity.Z < -50.f)
        {
            CurrentVelocity.Z = bArcadeMode ? -20.f : -30.f; // SLIGHTLY LESS restrictive
            BoatMesh->SetPhysicsLinearVelocity(CurrentVelocity);
        }
        
        // ADDED: Dampen upward velocity when underwater to prevent launching
        if (CurrentVelocity.Z > 100.f)
        {
            CurrentVelocity.Z *= 0.8f; // Reduce upward velocity by 20%
            BoatMesh->SetPhysicsLinearVelocity(CurrentVelocity);
        }
    }
    else if (DistanceUnderWater > -20.f)
    {
        // Near surface - gentle buoyancy to maintain floating
        const float SurfaceBuoyancy = BuoyancyForce * (bArcadeMode ? 1.5f : 1.2f); // REDUCED from 2x
        const FVector SurfaceForce = FVector(0.f, 0.f, SurfaceBuoyancy);
        BoatMesh->AddForce(SurfaceForce);
        
        // Add gentle upward bias to keep boat floating (REDUCED)
        const FVector FloatBias = FVector(0.f, 0.f, bArcadeMode ? 8000.f : 6000.f); // REDUCED from 12000
        BoatMesh->AddForce(FloatBias);
    }
    else if (DistanceUnderWater > -50.f)
    {
        // Slightly above water - gentle downward to settle on surface
        const FVector SettleForce = FVector(0.f, 0.f, bArcadeMode ? -5000.f : -7000.f); // INCREASED downward force
        BoatMesh->AddForce(SettleForce);
    }
    
    // Always stabilize rotation when near water (less aggressive in arcade mode for tricks)
    if (DistanceUnderWater > -100.f && !bIsInAir)
    {
        FVector AngularVel = BoatMesh->GetPhysicsAngularVelocityInRadians();
        float StabilizationForce = bArcadeMode ? 6000.f : 8000.f;
        BoatMesh->AddTorqueInRadians(-AngularVel * StabilizationForce * DeltaTime);
    }
}

void ABoatPawn::ApplyWaterDrag(float DeltaTime)
{
    // Enhanced water drag simulation with arcade adjustments
    const FVector BoatLocation = GetActorLocation();
    const float DistanceUnderWater = WaterLevel - BoatLocation.Z;
    
    if (DistanceUnderWater > -30.f) // CHANGED: Apply drag even when slightly above water
    {
        const float SubmersionRatio = FMath::Clamp((DistanceUnderWater + 30.f) / (SubmersionDepth + 30.f), 0.3f, 1.f); // Min 30% drag
        
        // Quadratic drag proportional to velocity^2 and submersion
        FVector V = BoatMesh->GetPhysicsLinearVelocity();
        const float Speed = V.Size();
        if (Speed > KINDA_SMALL_NUMBER)
        {
            FVector DragDir = -V.GetSafeNormal();
            // INCREASED drag to keep boat on water
            float DragMultiplier = bArcadeMode ? 0.0015f : 0.002f; // INCREASED from 0.001f
            float DragMag = WaterDensity * Speed * Speed * DragMultiplier * SubmersionRatio;
            BoatMesh->AddForce(DragDir * DragMag);
        }

        // Angular drag when in water (increased to prevent flipping)
        FVector W = BoatMesh->GetPhysicsAngularVelocityInRadians();
        if (!W.IsNearlyZero())
        {
            float AngularDragForce = bArcadeMode ? 2500.f : 3500.f; // INCREASED from 2000/3000
            BoatMesh->AddTorqueInRadians(-W * AngularDragForce * SubmersionRatio * DeltaTime);
        }
    }
}

// === INPUT SETUP WITH ARCADE CONTROLS ===
void ABoatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);
    
    // Traditional boat movement controls
    PlayerInputComponent->BindAxis("MoveForward", this, &ABoatPawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABoatPawn::MoveRight);
    
    // Mouse camera controls
    PlayerInputComponent->BindAxis("Turn", this, &ABoatPawn::MouseX);
    PlayerInputComponent->BindAxis("LookUp", this, &ABoatPawn::MouseY);
    
    // === ARCADE CONTROLS ===
    PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &ABoatPawn::StartBoost);
    PlayerInputComponent->BindAction("Boost", IE_Released, this, &ABoatPawn::StopBoost);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABoatPawn::Jump);
    PlayerInputComponent->BindAction("TrickLeft", IE_Pressed, this, &ABoatPawn::TrickLeft);
    PlayerInputComponent->BindAction("TrickRight", IE_Pressed, this, &ABoatPawn::TrickRight);
    
    // === TIME TRIAL CONTROLS ===
    PlayerInputComponent->BindAction("StartTimeTrial", IE_Pressed, this, &ABoatPawn::StartTimeTrialInput);
    PlayerInputComponent->BindAction("EndTimeTrial", IE_Pressed, this, &ABoatPawn::EndTimeTrialInput);
}

// === ORIGINAL INPUT FUNCTIONS ===
void ABoatPawn::MoveForward(float Value)
{
    ThrottleInput = FMath::Clamp(Value, -1.f, 1.f);
}

void ABoatPawn::MoveRight(float Value)
{
    SteeringInput = FMath::Clamp(Value, -1.f, 1.f);
}

void ABoatPawn::MouseX(float Value)
{
    if (bEnableMouseControl && FMath::Abs(Value) > 0.001f)
    {
        CameraYawInput += Value * MouseSensitivityX;
    }
}

void ABoatPawn::MouseY(float Value)
{
    if (bEnableMouseControl && FMath::Abs(Value) > 0.001f)
    {
        CameraPitchInput -= Value * MouseSensitivityY; // Inverted for natural feel
        CameraPitchInput = FMath::Clamp(CameraPitchInput, MinPitchAngle, MaxPitchAngle);
    }
}

// === TIME TRIAL SYSTEM IMPLEMENTATION ===

void ABoatPawn::StartTimeTrial(float Duration)
{
    if (bTimeTrialActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("?? Time Trial already active! End current trial first."));
        return;
    }

    // Initialize time trial
    bTimeTrialActive = true;
    TimeTrialTimeRemaining = Duration;
    TimeTrialCurrentScore = 0;
    
    // Enable arcade mode for time trial
    bool WasArcadeMode = bArcadeMode;
    bArcadeMode = true;
    
    // Reset boat state for fair start
    CurrentScore = 0;
    BoostEnergy = MaxBoostEnergy;
    bIsBoosting = false;
    bIsInAir = false;
    AirTime = 0.f;
    
    if (GEngine)
    {
        FString StartMessage = FString::Printf(TEXT("?? TIME TRIAL STARTED! Duration: %.0f seconds"), Duration);
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, StartMessage);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("?? TIME TRIAL STARTED! Duration: %.1f seconds, Score Multiplier: %.1fx"), 
        Duration, TimeTrialScoreMultiplier);
}

void ABoatPawn::EndTimeTrial()
{
    if (!bTimeTrialActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("?? No active time trial to end."));
        return;
    }

    // Calculate final results
    bool bNewBestScore = TimeTrialCurrentScore > TimeTrialBestScore;
    if (bNewBestScore)
    {
        TimeTrialBestScore = TimeTrialCurrentScore;
    }

    // Show results
    if (GEngine)
    {
        FString ResultsMessage = FString::Printf(
            TEXT("?? TIME TRIAL COMPLETE!\nFinal Score: %d\nBest Score: %d%s"), 
            TimeTrialCurrentScore, 
            TimeTrialBestScore,
            bNewBestScore ? TEXT(" (NEW RECORD!)") : TEXT("")
        );
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, ResultsMessage);
    }

    UE_LOG(LogTemp, Warning, TEXT("?? TIME TRIAL ENDED! Final Score: %d, Best: %d%s"), 
        TimeTrialCurrentScore, TimeTrialBestScore, bNewBestScore ? TEXT(" (NEW RECORD!)") : TEXT(""));

    // Reset time trial state
    bTimeTrialActive = false;
    TimeTrialTimeRemaining = 0.f;
    TimeTrialCurrentScore = 0;
}

void ABoatPawn::UpdateTimeTrialSystem(float DeltaTime)
{
    if (!bTimeTrialActive) return;

    // Update timer
    TimeTrialTimeRemaining -= DeltaTime;
    
    // Check if time trial should end
    if (TimeTrialTimeRemaining <= 0.f)
    {
        TimeTrialTimeRemaining = 0.f;
        EndTimeTrial();
        return;
    }
    
    // Show time trial UI periodically
    static float UIUpdateTimer = 0.f;
    UIUpdateTimer += DeltaTime;
    if (UIUpdateTimer >= 0.5f) // Update UI every half second
    {
        ShowTimeTrialUI();
        UIUpdateTimer = 0.f;
    }
}

void ABoatPawn::ShowTimeTrialUI()
{
    if (!bTimeTrialActive || !GEngine) return;
    
    // Format time remaining
    int32 Minutes = FMath::FloorToInt(TimeTrialTimeRemaining / 60.f);
    int32 Seconds = FMath::FloorToInt(TimeTrialTimeRemaining) % 60;
    int32 Milliseconds = FMath::FloorToInt((TimeTrialTimeRemaining - FMath::FloorToInt(TimeTrialTimeRemaining)) * 100);
    
    FString TimeString = FString::Printf(TEXT("%02d:%02d.%02d"), Minutes, Seconds, Milliseconds);
    
    // Display time trial status
    FString TimeTrialStatus = FString::Printf(
        TEXT("?? TIME TRIAL | %s | Score: %d | Best: %d"), 
        *TimeString, 
        TimeTrialCurrentScore, 
        TimeTrialBestScore
    );
    
    GEngine->AddOnScreenDebugMessage(999, 0.6f, FColor::Orange, TimeTrialStatus);
    
    // Warning when time is running low
    if (TimeTrialTimeRemaining <= 10.f)
    {
        FString WarningMsg = FString::Printf(TEXT("?? TIME RUNNING OUT: %.1f seconds!"), TimeTrialTimeRemaining);
        GEngine->AddOnScreenDebugMessage(998, 0.6f, FColor::Red, WarningMsg);
    }
}

void ABoatPawn::OnTimeTrialScoreAdded(int32 Points, const FString& Reason)
{
    if (!bTimeTrialActive) return;
    
    // Apply time trial score multiplier
    int32 TimeTrialPoints = FMath::RoundToInt(Points * TimeTrialScoreMultiplier);
    TimeTrialCurrentScore += TimeTrialPoints;
    
    // Show enhanced feedback for time trial scoring
    if (GEngine && !Reason.IsEmpty())
    {
        FString TimeTrialScoreMessage = FString::Printf(
            TEXT("?? +%d - %s (x%.1f multiplier)"), 
            TimeTrialPoints, 
            *Reason, 
            TimeTrialScoreMultiplier
        );
        GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, TimeTrialScoreMessage);
    }
}

// === CHECKPOINT SYSTEM INTEGRATION ===

void ABoatPawn::JoinCheckpointSystem(ACheckpointSystem* CheckpointSystem)
{
    if (!CheckpointSystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("?? Cannot join null checkpoint system"));
        return;
    }

    // Leave current system if any
    if (CurrentCheckpointSystem)
    {
        LeaveCheckpointSystem();
    }

    CurrentCheckpointSystem = CheckpointSystem;
    
    UE_LOG(LogTemp, Warning, TEXT("?? Boat joined checkpoint system with %d checkpoints"), 
        CheckpointSystem->GetTotalCheckpointCount());

    if (GEngine)
    {
        FString JoinMessage = FString::Printf(TEXT("?? Joined checkpoint race with %d checkpoints!"), 
            CheckpointSystem->GetTotalCheckpointCount());
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, JoinMessage);
    }
}

void ABoatPawn::LeaveCheckpointSystem()
{
    if (CurrentCheckpointSystem)
    {
        UE_LOG(LogTemp, Log, TEXT("?? Boat left checkpoint system"));
        CurrentCheckpointSystem = nullptr;
    }
}

void ABoatPawn::StartCheckpointRace()
{
    if (CurrentCheckpointSystem)
    {
        CurrentCheckpointSystem->StartSystem(this);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("?? No checkpoint system available to start race"));
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("?? No checkpoint system found!"));
        }
    }
}

// === CHECKPOINT INTERFACE IMPLEMENTATIONS ===

void ABoatPawn::NotifyCheckpointRaceStarted(ACheckpointSystem* CheckpointSystem)
{
    if (!CheckpointSystem) return;

    // If time trial is active, integrate the systems
    if (bTimeTrialActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint race started during time trial - enhanced scoring activated!"));
        
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, 
                TEXT("?? CHECKPOINT TIME TRIAL STARTED! Enhanced scoring active!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint race started!"));
        
        if (GEngine)
        {
            FString StartMessage = FString::Printf(TEXT("?? CHECKPOINT RACE STARTED!\n%d checkpoints to complete"), 
                CheckpointSystem->GetTotalCheckpointCount());
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, StartMessage);
        }
    }
}

void ABoatPawn::NotifyCheckpointRaceEnded(ACheckpointSystem* CheckpointSystem, bool bCompleted, float TotalTime, int32 FinalScore)
{
    if (!CheckpointSystem) return;

    FString CompletionStatus = bCompleted ? TEXT("COMPLETED") : TEXT("FAILED");
    FColor MessageColor = bCompleted ? FColor::Green : FColor::Red;

    UE_LOG(LogTemp, Warning, TEXT("?? Checkpoint race %s! Time: %.2f, Final Score: %d"), 
        *CompletionStatus, TotalTime, FinalScore);

    if (GEngine)
    {
        FString EndMessage = FString::Printf(
            TEXT("?? CHECKPOINT RACE %s!\nTime: %.2f seconds\nCheckpoint Score: %d"), 
            *CompletionStatus, TotalTime, FinalScore);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, MessageColor, EndMessage);
    }

    // If this was during a time trial, add bonus to time trial score
    if (bTimeTrialActive && bCompleted)
    {
        int32 CheckpointBonus = FinalScore * CheckpointBonusMultiplier;
        OnTimeTrialScoreAdded(CheckpointBonus, TEXT("Checkpoint Race Completion"));
        
        UE_LOG(LogTemp, Warning, TEXT("?? Time Trial Checkpoint Bonus: %d points (x%d multiplier)"), 
            CheckpointBonus, CheckpointBonusMultiplier);
    }
}

void ABoatPawn::NotifyCheckpointCompleted(ACheckpoint* Checkpoint, int32 CheckpointNumber, float CompletionTime)
{
    if (!Checkpoint) return;

    UE_LOG(LogTemp, Warning, TEXT("? Checkpoint %d '%s' completed in %.2f seconds!"), 
        CheckpointNumber, *Checkpoint->CheckpointName, CompletionTime);

    // Add to regular score system
    int32 CheckpointPoints = Checkpoint->BonusPoints > 0 ? Checkpoint->BonusPoints : 50;
    AddScore(CheckpointPoints, FString::Printf(TEXT("Checkpoint %d"), CheckpointNumber));

    // Special effects for different checkpoint types
    switch (Checkpoint->CheckpointType)
    {
        case ECheckpointType::Start:
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("?? RACE STARTED!"));
            }
            break;
            
        case ECheckpointType::Finish:
            if (GEngine)
            {
                FString FinishMessage = FString::Printf(TEXT("?? FINISH LINE! Time: %.2f"), CompletionTime);
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FinishMessage);
            }
            break;
            
        case ECheckpointType::Bonus:
            if (GEngine)
            {
                FString BonusMessage = FString::Printf(TEXT("? BONUS CHECKPOINT! +%.0f points"), Checkpoint->BonusPoints);
                GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, BonusMessage);
            }
            break;
            
        case ECheckpointType::TimeBonus:
            // Handle time bonus if in time trial
            if (bTimeTrialActive && Checkpoint->BonusTime > 0)
            {
                TimeTrialTimeRemaining += Checkpoint->BonusTime;
                if (GEngine)
                {
                    FString TimeBonusMessage = FString::Printf(TEXT("? TIME BONUS! +%.1f seconds"), Checkpoint->BonusTime);
                    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TimeBonusMessage);
                }
            }
            break;
    }
}

void ABoatPawn::NotifyCheckpointBonus(ACheckpoint* Checkpoint, float BonusPoints, float BonusTime)
{
    if (!Checkpoint) return;

    // Add bonus points to score
    if (BonusPoints > 0)
    {
        int32 Points = FMath::RoundToInt(BonusPoints);
        AddScore(Points, TEXT("Checkpoint Bonus"));
    }

    // Add bonus time if in time trial
    if (bTimeTrialActive && BonusTime > 0)
    {
        TimeTrialTimeRemaining += BonusTime;
        
        if (GEngine)
        {
            FString BonusMessage = FString::Printf(TEXT("?? CHECKPOINT BONUS!\nPoints: +%.0f\nTime: +%.1f sec"), 
                BonusPoints, BonusTime);
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, BonusMessage);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("?? Checkpoint bonus received: %.0f points, %.1f seconds"), BonusPoints, BonusTime);
}
