#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurrentVolume.generated.h"

class UBoxComponent;

UCLASS()
class ICPONDS_API ACurrentVolume : public AActor
{
    GENERATED_BODY()

public:
    ACurrentVolume();

    virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    UBoxComponent* Box;

public:
    UPROPERTY(EditAnywhere, Category="Current")
    FVector FlowDirection = FVector(1.f, 0.f, 0.f);

    UPROPERTY(EditAnywhere, Category="Current", meta=(ClampMin="0"))
    float FlowStrength = 2500.f; // approximate newtons

    UPROPERTY(EditAnywhere, Category="Current")
    bool bAffectNonPhysicsPawns = true;
};
