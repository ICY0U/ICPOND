#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PondTestSpawner.generated.h"

UCLASS()
class ICPONDS_API APondTestSpawner : public AActor
{
    GENERATED_BODY()

public:
    APondTestSpawner();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category="Pond")
    float PondRadius = 7000.f;

    UPROPERTY(EditAnywhere, Category="Pond")
    float IslandRingRadius = 6000.f;

    UPROPERTY(EditAnywhere, Category="Pond")
    int32 NumIslands = 9;

    UPROPERTY(EditAnywhere, Category="Pond")
    float CurrentStrength = 2000.f;

    UPROPERTY(EditAnywhere, Category="Pond")
    float CurrentRingHeight = 200.f;
};
