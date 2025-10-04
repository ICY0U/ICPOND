#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeTrialStartRing.generated.h"

/**
 * Start ring for time trials - drive through to start
 */
UCLASS()
class ICPONDS_API ATimeTrialStartRing : public AActor
{
    GENERATED_BODY()
    
public:    
    ATimeTrialStartRing();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    // === RING CONFIGURATION ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Start Ring")
    float RingRadius = 400.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Start Ring")
    float RingThickness = 50.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Start Ring")
    bool bAutoStartTimeTrial = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Start Ring")
    bool bAutoStartCheckpointRace = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Start Ring")
    float TimeTrialDuration = 90.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Start Ring")
    bool bShowDebugVisuals = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Start Ring")
    FLinearColor RingColor = FLinearColor::Green;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Start Ring")
    bool bOnlyTriggerOnce = false;

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* RingMesh;

    UPROPERTY(VisibleAnywhere, Category="Components")
    class UBoxComponent* RingTrigger;

    bool bHasTriggered = false;
    float PulseTimer = 0.f;

    UFUNCTION()
    void OnRingBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void StartRaceForBoat(AActor* BoatActor);
};