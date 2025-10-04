#include "TestRamp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"

ATestRamp::ATestRamp()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create root component
    USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    // Create ramp mesh
    RampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RampMesh"));
    RampMesh->SetupAttachment(RootComponent);
    RampMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    RampMesh->SetCollisionResponseToAllChannels(ECR_Block);
    RampMesh->SetCollisionObjectType(ECC_WorldStatic);
    RampMesh->SetSimulatePhysics(false); // Ramp should be static

    // Try to load a wedge/ramp mesh - try multiple options
    static ConstructorHelpers::FObjectFinder<UStaticMesh> WedgeMeshObj(TEXT("/Engine/BasicShapes/Wedge_A"));
    if (WedgeMeshObj.Succeeded())
    {
        RampMesh->SetStaticMesh(WedgeMeshObj.Object);
        UE_LOG(LogTemp, Log, TEXT("? Loaded Wedge mesh for ramp"));
    }
    else
    {
        // Fallback to cube if wedge not found
        static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshObj(TEXT("/Engine/BasicShapes/Cube"));
        if (CubeMeshObj.Succeeded())
        {
            RampMesh->SetStaticMesh(CubeMeshObj.Object);
            UE_LOG(LogTemp, Warning, TEXT("?? Using Cube as ramp (Wedge not found)"));
        }
    }

    // Create trigger volume for detection
    RampTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RampTrigger"));
    RampTrigger->SetupAttachment(RampMesh);
    RampTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    RampTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    RampTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    RampTrigger->SetGenerateOverlapEvents(true);

    // Bind overlap events
    RampTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATestRamp::OnRampBeginOverlap);
    RampTrigger->OnComponentEndOverlap.AddDynamic(this, &ATestRamp::OnRampEndOverlap);
}

void ATestRamp::BeginPlay()
{
    Super::BeginPlay();
    
    UpdateRampGeometry();
    
    UE_LOG(LogTemp, Warning, TEXT("?? TEST RAMP SPAWNED"));
    UE_LOG(LogTemp, Warning, TEXT("   - Length: %.0f, Width: %.0f, Height: %.0f"), 
        RampLength, RampWidth, RampHeight);
    UE_LOG(LogTemp, Warning, TEXT("   - Angle: %.0f°, Launch Boost: %.0f"), 
        RampAngle, LaunchBoost);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, 
            TEXT("?? TEST RAMP READY! Drive up it to launch!"));
    }
}

void ATestRamp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ADDED: Clean up old launch records (older than cooldown * 2)
    float CurrentTime = GetWorld()->GetTimeSeconds();
    TArray<AActor*> ActorsToRemove;
    
    for (auto& Pair : LaunchedActors)
    {
        if (CurrentTime - Pair.Value > LaunchCooldown * 2.f)
        {
            ActorsToRemove.Add(Pair.Key);
        }
    }
    
    for (AActor* Actor : ActorsToRemove)
    {
        LaunchedActors.Remove(Actor);
    }

    // Draw debug visuals
    if (bShowDebugVisuals && GetWorld())
    {
        FVector RampLocation = GetActorLocation();
        FVector ForwardDir = GetActorForwardVector();
        FVector UpDir = GetActorUpVector();
        
        // Draw ramp outline
        FVector RampStart = RampLocation - (ForwardDir * RampLength * 0.5f);
        FVector RampEnd = RampLocation + (ForwardDir * RampLength * 0.5f) + (UpDir * RampHeight);
        
        DrawDebugLine(GetWorld(), RampStart, RampEnd, FColor::Orange, false, -1.f, 0, 10.f);
        
        // Draw approach direction
        FVector ApproachStart = RampStart - (ForwardDir * 500.f);
        DrawDebugDirectionalArrow(GetWorld(), ApproachStart, RampStart, 
            100.f, FColor::Green, false, -1.f, 0, 5.f);
        
        // Draw launch trajectory
        FVector LaunchStart = RampEnd;
        FVector LaunchEnd = LaunchStart + (ForwardDir * 500.f) + (UpDir * 300.f);
        DrawDebugDirectionalArrow(GetWorld(), LaunchStart, LaunchEnd, 
            100.f, FColor::Yellow, false, -1.f, 0, 5.f);
    }
}

void ATestRamp::OnRampBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor) return;

    // Check if it's a pawn (boat)
    APawn* Pawn = Cast<APawn>(OtherActor);
    if (Pawn)
    {
        // ADDED: Check cooldown - prevent launching same actor repeatedly
        float CurrentTime = GetWorld()->GetTimeSeconds();
        float* LastLaunchTime = LaunchedActors.Find(OtherActor);
        
        if (LastLaunchTime != nullptr)
        {
            float TimeSinceLastLaunch = CurrentTime - *LastLaunchTime;
            if (TimeSinceLastLaunch < LaunchCooldown)
            {
                // Still in cooldown, don't launch again
                UE_LOG(LogTemp, Log, TEXT("?? Ramp cooldown active (%.1fs remaining)"), 
                    LaunchCooldown - TimeSinceLastLaunch);
                return;
            }
        }
        
        UE_LOG(LogTemp, Warning, TEXT("?? BOAT ENTERED RAMP: %s"), *OtherActor->GetName());
        
        // Apply launch force
        ApplyLaunchForce(OtherActor);
        
        // ADDED: Record launch time
        LaunchedActors.Add(OtherActor, CurrentTime);
        
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("?? LAUNCHING!"));
        }
    }
}

void ATestRamp::OnRampEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!OtherActor) return;

    APawn* Pawn = Cast<APawn>(OtherActor);
    if (Pawn)
    {
        UE_LOG(LogTemp, Log, TEXT("?? BOAT LEFT RAMP: %s"), *OtherActor->GetName());
    }
}

void ATestRamp::ApplyLaunchForce(AActor* BoatActor)
{
    if (!BoatActor) return;

    // Get boat's mesh component with physics
    UPrimitiveComponent* BoatPhysics = Cast<UPrimitiveComponent>(
        BoatActor->GetRootComponent()
    );

    if (!BoatPhysics || !BoatPhysics->IsSimulatingPhysics())
    {
        // Try to find a physics component
        TArray<UPrimitiveComponent*> PhysicsComponents;
        BoatActor->GetComponents<UPrimitiveComponent>(PhysicsComponents);
        
        for (UPrimitiveComponent* Component : PhysicsComponents)
        {
            if (Component && Component->IsSimulatingPhysics())
            {
                BoatPhysics = Component;
                break;
            }
        }
    }

    if (BoatPhysics && BoatPhysics->IsSimulatingPhysics())
    {
        // FIXED: More controlled launch with better physics
        FVector CurrentVelocity = BoatPhysics->GetPhysicsLinearVelocity();
        float CurrentSpeed = CurrentVelocity.Size();
        
        // Calculate launch direction based on ramp angle
        FVector ForwardDir = GetActorForwardVector();
        FVector UpDir = FVector::UpVector; // Use world up for consistent launches
        
        float AngleRad = FMath::DegreesToRadians(RampAngle);
        FVector LaunchDirection = (ForwardDir * FMath::Cos(AngleRad)) + (UpDir * FMath::Sin(AngleRad));
        LaunchDirection.Normalize();
        
        // REDUCED: Scale launch boost based on current speed (30-60% of setting)
        float SpeedMultiplier = FMath::Clamp(CurrentSpeed / 1000.f, 0.3f, 0.6f);
        float AdjustedBoost = LaunchBoost * SpeedMultiplier;
        
        // Apply more controlled launch impulse
        FVector LaunchImpulse = LaunchDirection * AdjustedBoost * BoatPhysics->GetMass();
        BoatPhysics->AddImpulse(LaunchImpulse, NAME_None, true);
        
        // ADDED: Preserve some forward momentum
        FVector ForwardMomentum = ForwardDir * CurrentSpeed * 0.5f;
        BoatPhysics->SetPhysicsLinearVelocity(
            BoatPhysics->GetPhysicsLinearVelocity() + ForwardMomentum
        );
        
        UE_LOG(LogTemp, Warning, TEXT("?? APPLIED LAUNCH: Speed=%.0f, Boost=%.0f (Angle: %.0f°)"), 
            CurrentSpeed, AdjustedBoost, RampAngle);
        
        if (GEngine)
        {
            FString LaunchMsg = FString::Printf(TEXT("?? RAMP LAUNCH! Speed: %.0f"), CurrentSpeed);
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, LaunchMsg);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("?? Could not find physics component on boat"));
    }
}

void ATestRamp::UpdateRampGeometry()
{
    if (!RampMesh) return;

    // Scale the mesh to match ramp dimensions
    FVector Scale;
    Scale.X = RampLength / 100.f; // Length
    Scale.Y = RampWidth / 100.f;  // Width
    Scale.Z = RampHeight / 100.f; // Height
    
    RampMesh->SetWorldScale3D(Scale);
    
    // Rotate to create ramp angle - FIXED: Rotate around Y axis for proper ramp orientation
    FRotator RampRotation = GetActorRotation();
    RampRotation.Pitch = -RampAngle; // Negative for upward slope
    RampRotation.Roll = 0.f;
    RampRotation.Yaw = GetActorRotation().Yaw; // Keep actor's yaw
    
    // Position the mesh so the bottom is at the actor origin
    FVector MeshOffset;
    MeshOffset.X = RampLength * 0.5f; // Center along length
    MeshOffset.Y = 0.f;
    MeshOffset.Z = 0.f; // Bottom at origin
    
    RampMesh->SetRelativeLocation(MeshOffset);
    RampMesh->SetRelativeRotation(FRotator(-RampAngle, 0.f, 0.f));
    
    // Position trigger - make it cover the entire ramp surface
    if (RampTrigger)
    {
        FVector TriggerExtent;
        TriggerExtent.X = RampLength * 0.6f;
        TriggerExtent.Y = RampWidth * 0.6f;
        TriggerExtent.Z = RampHeight * 0.6f;
        
        RampTrigger->SetBoxExtent(TriggerExtent);
        
        // Position trigger in the middle of the ramp
        FVector TriggerOffset;
        TriggerOffset.X = RampLength * 0.5f;
        TriggerOffset.Y = 0.f;
        TriggerOffset.Z = RampHeight * 0.3f;
        RampTrigger->SetRelativeLocation(TriggerOffset);
        RampTrigger->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
    }
    
    UE_LOG(LogTemp, Log, TEXT("?? Ramp geometry updated: Scale(%.2f, %.2f, %.2f), Angle: %.0f°"), 
        Scale.X, Scale.Y, Scale.Z, RampAngle);
}