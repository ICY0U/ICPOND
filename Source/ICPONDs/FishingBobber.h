#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FishingBobber.generated.h"

UCLASS()
class ICPONDS_API AFishingBobber : public AActor
{
    GENERATED_BODY()

public:
    AFishingBobber();

    virtual void Tick(float DeltaTime) override;

    void SetWaterLevel(float InZ) { WaterLevelZ = InZ; }
    bool IsBiting() const { return bBiting; }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* Sphere;

    UPROPERTY(EditAnywhere, Category="Bobber")
    float BuoyancyStrength = 22000.f;

    UPROPERTY(EditAnywhere, Category="Bobber")
    float LinearDrag = 0.9f;

    UPROPERTY(EditAnywhere, Category="Bobber")
    float BobbingAmplitude = 6.f;

    UPROPERTY(EditAnywhere, Category="Bobber")
    float BobbingFrequency = 1.8f;

    float WaterLevelZ = 0.f;
    bool bBiting = false;
    FTimerHandle BiteTimerHandle;
    FTimerHandle ResetBiteTimerHandle;

    void TriggerBite();
    void ClearBite();
};
