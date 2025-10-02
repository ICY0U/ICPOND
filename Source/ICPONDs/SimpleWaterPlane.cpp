\
#include "SimpleWaterPlane.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"

ASimpleWaterPlane::ASimpleWaterPlane()
{
    PrimaryActorTick.bCanEverTick = false;

    Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
    SetRootComponent(Plane);
    Plane->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));
    if (PlaneMesh.Succeeded())
    {
        Plane->SetStaticMesh(PlaneMesh.Object);
        Plane->SetWorldScale3D(FVector(150.f, 150.f, 1.f)); // ~150m square
    }

    // Try to use a water material from the Water plugin; otherwise fallback to basic shape material
    UMaterialInterface* Mat = nullptr;
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> WaterMat1(TEXT("/Water/Materials/M_Water_LargeOcean.M_Water_LargeOcean"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> WaterMat2(TEXT("/Water/Materials/M_Water_Ocean.M_Water_Ocean"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> BasicMat(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));

    if (WaterMat1.Succeeded()) Mat = WaterMat1.Object;
    else if (WaterMat2.Succeeded()) Mat = WaterMat2.Object;
    else if (BasicMat.Succeeded()) Mat = BasicMat.Object;

    if (Mat)
    {
        Plane->SetMaterial(0, Mat);
    }

    SetActorLocation(FVector(0.f, 0.f, 0.f));
}
void ASimpleWaterPlane::BeginPlay()
{
    Super::BeginPlay();
}
