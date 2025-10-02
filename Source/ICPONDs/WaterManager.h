#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterManager.generated.h"

UCLASS()
class ICPONDS_API AWaterManager : public AActor
{
    GENERATED_BODY()

public:
    AWaterManager();

    virtual void Tick(float DeltaTime) override;

    // Water properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
    float WaterLevel = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
    float WaveAmplitude = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
    float WaveFrequency = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
    float WaveSpeed = 2.f;

    // Get water height at specific location (including waves)
    UFUNCTION(BlueprintCallable, Category = "Water")
    float GetWaterHeightAtLocation(const FVector& Location) const;

    // Check if a location is underwater
    UFUNCTION(BlueprintCallable, Category = "Water")
    bool IsLocationUnderwater(const FVector& Location) const;

protected:
    virtual void BeginPlay() override;

private:
    float GameTime = 0.f;
};