#include "BoatPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/PlayerInput.h"
#include "FishingBobber.h"
#include "Engine/EngineTypes.h"

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
    BoatMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoatMesh->SetCollisionProfileName(TEXT("BlockAll"));

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
    Camera->SetFieldOfView(70.f); // Wide FOV to see the boat

    AutoPossessPlayer = EAutoReceiveInput::Player0;
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
        UE_LOG(LogTemp, Warning, TEXT("Custom boat repositioned above water at Z: %.1f"), CurrentLocation.Z);
    }
    
    // Initialize water level to 0 as default
    WaterLevel = 0.f;
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
            
            UE_LOG(LogTemp, Error, TEXT("EMERGENCY TELEPORT - Custom boat was at Z: %.1f, moved to Z: %.1f"), 
                CurrentLocation.Z, SafeLocation.Z);
        }
        
        // Apply buoyancy forces
        ApplyBuoyancy(DeltaTime);

        // Apply boat movement forces
        const FVector Forward = GetActorForwardVector();
        const FVector Force = Forward * (ThrottleInput * MaxThrust);
        BoatMesh->AddForce(Force);

        // Apply turning torque
        const FVector Torque = FVector(0.f, 0.f, SteeringInput * TurnTorque);
        BoatMesh->AddTorqueInRadians(Torque);

        // Update camera dynamics for cinematic feel
        UpdateCameraDynamics(DeltaTime);

        // Cap speed
        const FVector Vel = BoatMesh->GetPhysicsLinearVelocity();
        const float Speed = Vel.Size();
        if (Speed > MaxSpeed)
        {
            const FVector Clamped = Vel.GetSafeNormal() * MaxSpeed;
            BoatMesh->SetPhysicsLinearVelocity(Clamped);
        }

        ApplyWaterDrag(DeltaTime);

        // Debug display movement state
        if (GEngine && GetWorld()->GetTimeSeconds() - LastDebugTime > 1.0f)
        {
            FString MoveDebug = FString::Printf(TEXT("Throttle: %.2f | Steering: %.2f | Speed: %.1f cm/s"), 
                ThrottleInput, SteeringInput, Speed);
            GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, MoveDebug);
            LastDebugTime = GetWorld()->GetTimeSeconds();
        }
    }
}

void ABoatPawn::UpdateCameraDynamics(float DeltaTime)
{
    if (!SpringArm || !Camera) return;

    // Base camera position and rotation (now influenced by mouse)
    FVector BaseLocation = FVector(-100.f, 0.f, 80.f);
    FRotator BaseRotation = FRotator(-30.f + CameraPitchInput, CameraYawInput, 0.f);
    
    // Add subtle camera shake when moving
    FVector CameraShake = FVector::ZeroVector;
    float ShakeIntensity = 0.f;
    
    if (FMath::Abs(ThrottleInput) > 0.1f)
    {
        ShakeIntensity = FMath::Abs(ThrottleInput) * CameraShakeIntensity;
        CameraShake = FVector(
            FMath::Sin(GetWorld()->GetTimeSeconds() * 8.f) * ShakeIntensity,
            FMath::Cos(GetWorld()->GetTimeSeconds() * 6.f) * ShakeIntensity * 0.5f,
            FMath::Sin(GetWorld()->GetTimeSeconds() * 10.f) * ShakeIntensity * 0.3f
        );
    }
    
    // Add slight camera movement based on boat velocity for dynamic feel
    FVector BoatVelocity = BoatMesh->GetPhysicsLinearVelocity();
    float VelocityInfluence = FMath::Clamp(BoatVelocity.Size() / MaxSpeed, 0.f, 1.f);
    
    // Camera leans slightly based on turning (but don't override mouse control)
    FVector AngularVel = BoatMesh->GetPhysicsAngularVelocityInRadians();
    float TurnLean = AngularVel.Z * 10.f; // Convert to degrees
    
    // Dynamic camera positioning (reduced effects when mouse controlling)
    float EffectStrength = bEnableMouseControl ? 0.3f : 1.0f; // Reduce automatic effects when mouse controlling
    FVector DynamicOffset = CameraShake + FVector(
        -VelocityInfluence * 15.f * EffectStrength, // Pull back slightly when moving fast
        TurnLean * 2.f * EffectStrength, // Lean with turns (reduced)
        VelocityInfluence * 8.f * EffectStrength // Rise slightly when moving fast
    );
    
    // Dynamic rotation adjustments (subtle when mouse controlling)
    FRotator DynamicRotation = BaseRotation + FRotator(
        VelocityInfluence * -5.f * EffectStrength, // Look down more when moving fast
        TurnLean * 0.5f * EffectStrength, // Slight yaw with turns
        TurnLean * 0.3f * EffectStrength // Slight roll with turns
    );
    
    // Smoothly interpolate to target position and rotation
    FVector TargetLocation = BaseLocation + DynamicOffset;
    FVector CurrentLocation = SpringArm->GetRelativeLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, CameraFollowSpeed);
    SpringArm->SetRelativeLocation(NewLocation);
    
    FRotator CurrentRotation = SpringArm->GetRelativeRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DynamicRotation, DeltaTime, CameraFollowSpeed * 2.f); // Faster rotation response
    SpringArm->SetRelativeRotation(NewRotation);

    // Debug display mouse input
    if (GEngine && GetWorld()->GetTimeSeconds() - LastDebugTime > 1.0f)
    {
        FString CameraDebug = FString::Printf(TEXT("Camera Yaw: %.1f° | Pitch: %.1f° | Mouse Control: %s"), 
            CameraYawInput, CameraPitchInput, bEnableMouseControl ? TEXT("ON") : TEXT("OFF"));
        GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Yellow, CameraDebug);
        LastDebugTime = GetWorld()->GetTimeSeconds();
    }
}

void ABoatPawn::ApplyBuoyancy(float DeltaTime)
{
    const FVector BoatLocation = GetActorLocation();
    const float DistanceUnderWater = WaterLevel - BoatLocation.Z;
    
    // Apply buoyancy forces based on submersion
    if (DistanceUnderWater > 0.f)
    {
        // Underwater - apply strong upward force
        float UltraBuoyancy = 150000.f; // Increased base force
        
        // Scale force with depth for stronger response
        if (DistanceUnderWater > 50.f)
        {
            UltraBuoyancy *= (DistanceUnderWater / 50.f);
        }
        
        const FVector MegaBuoyancyForce = FVector(0.f, 0.f, UltraBuoyancy);
        BoatMesh->AddForce(MegaBuoyancyForce);
        
        // Counter gravity more aggressively
        const float GravityCounterForce = BoatMesh->GetMass() * 980.f * 3.f; // 3x gravity compensation
        BoatMesh->AddForce(FVector(0.f, 0.f, GravityCounterForce));
        
        // Limit downward velocity more aggressively
        FVector CurrentVelocity = BoatMesh->GetPhysicsLinearVelocity();
        if (CurrentVelocity.Z < -50.f)
        {
            CurrentVelocity.Z = -25.f; // Slower fall speed
            BoatMesh->SetPhysicsLinearVelocity(CurrentVelocity);
        }
    }
    else if (DistanceUnderWater > -20.f)
    {
        // Near surface - gentle buoyancy to maintain floating
        const float SurfaceBuoyancy = BuoyancyForce * 1.5f;
        const FVector SurfaceForce = FVector(0.f, 0.f, SurfaceBuoyancy);
        BoatMesh->AddForce(SurfaceForce);
        
        // Add gentle upward bias to keep boat floating
        const FVector FloatBias = FVector(0.f, 0.f, 8000.f);
        BoatMesh->AddForce(FloatBias);
    }
    else if (DistanceUnderWater > -50.f)
    {
        // Slightly above water - gentle downward to settle on surface
        const FVector SettleForce = FVector(0.f, 0.f, -5000.f);
        BoatMesh->AddForce(SettleForce);
    }
    
    // Always stabilize rotation when near water
    if (DistanceUnderWater > -100.f)
    {
        FVector AngularVel = BoatMesh->GetPhysicsAngularVelocityInRadians();
        BoatMesh->AddTorqueInRadians(-AngularVel * 8000.f * DeltaTime);
    }
}

void ABoatPawn::ApplyWaterDrag(float DeltaTime)
{
    // Enhanced water drag simulation
    const FVector BoatLocation = GetActorLocation();
    const float DistanceUnderWater = WaterLevel - BoatLocation.Z;
    
    if (DistanceUnderWater > 0.f)
    {
        const float SubmersionRatio = FMath::Clamp(DistanceUnderWater / SubmersionDepth, 0.f, 1.f);
        
        // Quadratic drag proportional to velocity^2 and submersion
        FVector V = BoatMesh->GetPhysicsLinearVelocity();
        const float Speed = V.Size();
        if (Speed > KINDA_SMALL_NUMBER)
        {
            FVector DragDir = -V.GetSafeNormal();
            float DragMag = WaterDensity * Speed * Speed * 0.0015f * SubmersionRatio; // Standard boat drag
            BoatMesh->AddForce(DragDir * DragMag);
        }

        // Angular drag when in water
        FVector W = BoatMesh->GetPhysicsAngularVelocityInRadians();
        if (!W.IsNearlyZero())
        {
            BoatMesh->AddTorqueInRadians(-W * 3000.f * SubmersionRatio * DeltaTime); // Standard angular drag
        }
    }
}

void ABoatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);
    
    // Traditional boat movement controls
    PlayerInputComponent->BindAxis("MoveForward", this, &ABoatPawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABoatPawn::MoveRight);
    
    // Mouse camera controls
    PlayerInputComponent->BindAxis("Turn", this, &ABoatPawn::MouseX);
    PlayerInputComponent->BindAxis("LookUp", this, &ABoatPawn::MouseY);
    
    // Keep fishing controls
    PlayerInputComponent->BindAction("Fish", IE_Pressed, this, &ABoatPawn::StartFish);
    PlayerInputComponent->BindAction("Fish", IE_Released, this, &ABoatPawn::StopFish);
}

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

void ABoatPawn::StartFish()
{
    if (ActiveBobber) return;

    const FVector SpawnLoc = GetActorLocation() + GetActorForwardVector() * CastDistance + FVector(0,0,50);
    const FRotator SpawnRot = FRotator::ZeroRotator;

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AFishingBobber* Bobber = GetWorld()->SpawnActor<AFishingBobber>(AFishingBobber::StaticClass(), SpawnLoc, SpawnRot, Params);
    if (Bobber)
    {
        Bobber->SetWaterLevel(0.f); // our SimpleWaterPlane sits at Z=0
        if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Bobber->GetRootComponent()))
        {
            Prim->AddImpulse(GetActorForwardVector() * CastImpulse);
        }
        ActiveBobber = Bobber;
        UE_LOG(LogTemp, Log, TEXT("Fishing: cast"));
    }
}

void ABoatPawn::StopFish()
{
    if (!ActiveBobber) return;

    const bool bCaught = ActiveBobber->IsBiting();
    if (bCaught)
    {
        static const TCHAR* FishTypes[] = { TEXT("Minnow"), TEXT("Perch"), TEXT("Carp"), TEXT("Golden Koi") };
        int32 Index = FMath::RandRange(0, 3);
        UE_LOG(LogTemp, Log, TEXT("Fishing: Caught a %s!"), FishTypes[Index]);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Fishing: reeled in too early."));
    }

    ActiveBobber->Destroy();
    ActiveBobber = nullptr;
}
