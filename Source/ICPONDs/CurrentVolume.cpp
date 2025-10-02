\
#include "CurrentVolume.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Pawn.h"

ACurrentVolume::ACurrentVolume()
{
    PrimaryActorTick.bCanEverTick = true;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    SetRootComponent(Box);
    Box->InitBoxExtent(FVector(500.f, 500.f, 200.f));
    Box->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ACurrentVolume::BeginPlay()
{
    Super::BeginPlay();
    FlowDirection = FlowDirection.GetSafeNormal();
}

void ACurrentVolume::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    TArray<AActor*> OverlappingActors;
    Box->GetOverlappingActors(OverlappingActors);

    for (AActor* A : OverlappingActors)
    {
        if (!A) continue;

        if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(A->GetRootComponent()))
        {
            if (Prim->IsSimulatingPhysics())
            {
                Prim->AddForce(FlowDirection * FlowStrength);
                continue;
            }
        }

        if (bAffectNonPhysicsPawns)
        {
            if (APawn* P = Cast<APawn>(A))
            {
                FVector Loc = P->GetActorLocation();
                Loc += (FlowDirection * FlowStrength * 0.0002f) * DeltaSeconds; // gentle nudge
                P->SetActorLocation(Loc, true);
            }
        }
    }
}
