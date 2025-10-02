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

    BoatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoatMesh"));
    SetRootComponent(BoatMesh);
    BoatMesh->SetSimulatePhysics(true);
    BoatMesh->SetLinearDamping(0.1f); // Very low damping for responsive buoyancy
    BoatMesh->SetAngularDamping(2.5f);
    BoatMesh->SetEnableGravity(true); // Enable gravity for buoyancy
    BoatMesh->BodyInstance.bUseCCD = true;
    BoatMesh->SetMassOverrideInKg(NAME_None, 200.f); // Lighter boat for easier floating
    BoatMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Ensure collision is enabled
    BoatMesh->SetCollisionProfileName(TEXT("BlockAll")); // Use standard collision profile

    // Use an engine basic shape so no content is required.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> HullMeshObj(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    if (HullMeshObj.Succeeded())
    {
        BoatMesh->SetStaticMesh(HullMeshObj.Object);
        BoatMesh->SetWorldScale3D(FVector(1.5f, 0.6f, 0.4f));
    }

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(BoatMesh);
    SpringArm->TargetArmLength = 900.f;
    SpringArm->bDoCollisionTest = false;
    SpringArm->bUsePawnControlRotation = false;
    SpringArm->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

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
        UE_LOG(LogTemp, Warning, TEXT("Boat repositioned above water at Z: %.1f"), CurrentLocation.Z);
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
            
            UE_LOG(LogTemp, Error, TEXT("EMERGENCY TELEPORT - Boat was at Z: %.1f, moved to Z: %.1f"), 
                CurrentLocation.Z, SafeLocation.Z);
        }
        
        // Apply buoyancy forces
        ApplyBuoyancy(DeltaTime);

        const FVector Forward = GetActorForwardVector();
        const FVector Force = Forward * (ThrottleInput * MaxThrust);
        BoatMesh->AddForce(Force);

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

        ApplyWaterDrag(DeltaTime);
    }
}

void ABoatPawn::ApplyBuoyancy(float DeltaTime)
{
    const FVector BoatLocation = GetActorLocation();
    const float DistanceUnderWater = WaterLevel - BoatLocation.Z;
    
    // Debug logging to see what's happening
    if (GEngine && GetWorld()->GetTimeSeconds() - LastDebugTime > 1.0f)
    {
        FString DebugMsg = FString::Printf(TEXT("Boat Z: %.1f, Water Level: %.1f, Distance Under: %.1f"), 
            BoatLocation.Z, WaterLevel, DistanceUnderWater);
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, DebugMsg);
        LastDebugTime = GetWorld()->GetTimeSeconds();
    }
    
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
            float DragMag = WaterDensity * Speed * Speed * 0.0015f * SubmersionRatio;
            BoatMesh->AddForce(DragDir * DragMag);
        }

        // Angular drag when in water
        FVector W = BoatMesh->GetPhysicsAngularVelocityInRadians();
        if (!W.IsNearlyZero())
        {
            BoatMesh->AddTorqueInRadians(-W * 3000.f * SubmersionRatio * DeltaTime);
        }
    }
}

void ABoatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ABoatPawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABoatPawn::MoveRight);
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
