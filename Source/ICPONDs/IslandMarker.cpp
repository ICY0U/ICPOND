\
#include "IslandMarker.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AIslandMarker::AIslandMarker()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    Mesh->SetSimulatePhysics(false);
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMesh(TEXT("/Engine/BasicShapes/Cone.Cone"));
    if (ConeMesh.Succeeded())
    {
        Mesh->SetStaticMesh(ConeMesh.Object);
        Mesh->SetWorldScale3D(FVector(2.0f, 2.0f, 1.2f));
    }

    Label = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Label"));
    Label->SetupAttachment(Mesh);
    Label->SetWorldSize(150.f);
    Label->SetHorizontalAlignment(EHTA_Center);
    Label->SetRelativeLocation(FVector(0.f, 0.f, 300.f));
}
