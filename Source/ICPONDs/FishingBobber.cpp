#include "FishingBobber.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AFishingBobber::AFishingBobber()
{
    PrimaryActorTick.bCanEverTick = true;

    Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
    SetRootComponent(Sphere);
    Sphere->SetSimulatePhysics(true);
    Sphere->SetLinearDamping(1.2f);
    Sphere->SetAngularDamping(1.0f);
    Sphere->SetEnableGravity(true);
    Sphere->BodyInstance.bUseCCD = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        Sphere->SetStaticMesh(SphereMesh.Object);
        Sphere->SetWorldScale3D(FVector(0.2f));
    }
}

void AFishingBobber::BeginPlay()
{
    Super::BeginPlay();
    // schedule a bite sometime soon
    const float FirstBiteIn = FMath::FRandRange(1.5f, 4.0f);
    GetWorldTimerManager().SetTimer(BiteTimerHandle, this, &AFishingBobber::TriggerBite, FirstBiteIn, false);
}

void AFishingBobber::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!Sphere || !Sphere->IsSimulatingPhysics()) return;

    const FVector Loc = GetActorLocation();
    const FVector Vel = Sphere->GetPhysicsLinearVelocity();
    const float Depth = (WaterLevelZ - Loc.Z);

    // Enhanced buoyancy: stronger when deeper underwater
    if (Depth > 0.f)
    {
        const float BuoyancyMultiplier = FMath::Clamp(Depth / 50.f, 0.1f, 2.0f); // Scale based on depth
        const float UpForce = Depth * BuoyancyStrength * BuoyancyMultiplier;
        Sphere->AddForce(FVector(0.f, 0.f, UpForce));
        
        // Add surface tension effect near water surface
        if (Depth < 10.f)
        {
            const float SurfaceTension = (10.f - Depth) * 500.f;
            Sphere->AddForce(FVector(0.f, 0.f, -SurfaceTension));
        }
    }

    // Enhanced lateral drag in water
    if (Depth > -5.f) // Apply drag even slightly above water
    {
        const FVector HorizontalVel = FVector(Vel.X, Vel.Y, 0.f);
        const FVector Drag = -HorizontalVel * LinearDrag * DeltaTime;
        Sphere->AddForce(Drag);
    }

    // Enhanced bobbing when near surface with wave simulation
    if (FMath::Abs(Depth) < 20.f)
    {
        const float WaveHeight = FMath::Sin(GetWorld()->GetTimeSeconds() * BobbingFrequency) * BobbingAmplitude;
        const float TargetZ = WaterLevelZ + WaveHeight;
        
        if (Loc.Z < TargetZ)
        {
            const float RestoreForce = (TargetZ - Loc.Z) * 800.f;
            Sphere->AddForce(FVector(0.f, 0.f, RestoreForce));
        }
        
        // Add random wave motion for more realism
        const float RandomWave = FMath::Sin(GetWorld()->GetTimeSeconds() * 2.3f + GetActorLocation().X * 0.01f) * 3.f;
        Sphere->AddForce(FVector(RandomWave * 10.f, 0.f, 0.f));
    }
}

void AFishingBobber::TriggerBite()
{
    bBiting = true;
    // bite lasts briefly
    GetWorldTimerManager().SetTimer(ResetBiteTimerHandle, this, &AFishingBobber::ClearBite, FMath::FRandRange(1.2f, 2.0f), false);
}

void AFishingBobber::ClearBite()
{
    bBiting = false;
    // schedule next bite
    GetWorldTimerManager().SetTimer(BiteTimerHandle, this, &AFishingBobber::TriggerBite, FMath::FRandRange(3.0f, 6.0f), false);
}
