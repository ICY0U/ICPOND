#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestRamp.generated.h"

/**
 * Test ramp for boat jumping with proper collision and detection
 */
UCLASS()
class ICPONDS_API ATestRamp : public AActor
{
    GENERATED_BODY()
    
public:    
    ATestRamp();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    // === RAMP CONFIGURATION ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ramp")
    float RampLength = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ramp")
    float RampWidth = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ramp")
    float RampHeight = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ramp")
    float RampAngle = 25.f; // Degrees

    // REDUCED: Default launch boost for more controlled jumps
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ramp")
    float LaunchBoost = 30000.f; // Launch force (reduced from 50000 for better control)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ramp")
    bool bShowDebugVisuals = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ramp")
    FLinearColor RampColor = FLinearColor(1.0f, 0.5f, 0.0f); // Orange

    // ADDED: Cooldown to prevent multiple launches
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ramp")
    float LaunchCooldown = 2.f; // Seconds before can launch again

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* RampMesh;

    UPROPERTY(VisibleAnywhere, Category="Components")
    class UBoxComponent* RampTrigger;

    // ADDED: Track which actors have been launched recently
    TMap<AActor*, float> LaunchedActors; // Actor -> Time of last launch
    
    UFUNCTION()
    void OnRampBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnRampEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void ApplyLaunchForce(AActor* BoatActor);
    void UpdateRampGeometry();
};