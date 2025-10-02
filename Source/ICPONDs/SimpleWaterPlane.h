#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleWaterPlane.generated.h"

UCLASS()
class ICPONDS_API ASimpleWaterPlane : public AActor
{
    GENERATED_BODY()

public:
    ASimpleWaterPlane();

    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* Plane;

protected:
    virtual void BeginPlay() override;
};
