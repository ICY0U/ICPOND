#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "ArcadePowerUp.generated.h"

UENUM(BlueprintType)
enum class EPowerUpType : uint8
{
    SpeedBoost,     // Temporary speed increase
    BoostRefill,    // Refill boost energy
    ScoreMultiplier, // 2x score for a duration
    JumpPower,      // Enhanced jump force
    Invincibility,  // Brief invincibility
    MegaPoints      // Instant large score bonus
};

UCLASS()
class ICPONDS_API AArcadePowerUp : public AActor
{
    GENERATED_BODY()

public:
    AArcadePowerUp();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PowerUp")
    EPowerUpType PowerUpType = EPowerUpType::SpeedBoost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PowerUp")
    float EffectDuration = 10.f; // Duration for temporary effects

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PowerUp")
    int32 PointsValue = 100; // Points for instant score powerups

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PowerUp")
    float RespawnTime = 30.f; // Time before respawning after collection

    // Public access to power-up info
    UFUNCTION(BlueprintCallable, Category="PowerUp")
    FString GetPowerUpName() const;

    UFUNCTION(BlueprintCallable, Category="PowerUp")
    FLinearColor GetPowerUpColor() const;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
        UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
        const FHitResult& SweepResult);

private:
    UPROPERTY(VisibleAnywhere, Category="Components")
    USphereComponent* CollisionSphere;

    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere, Category="Components")
    UParticleSystemComponent* GlowParticles;

    UPROPERTY(VisibleAnywhere, Category="Components")
    UAudioComponent* AmbientAudio;

    UPROPERTY(EditAnywhere, Category="PowerUp")
    float FloatSpeed = 50.f; // Speed of floating animation

    UPROPERTY(EditAnywhere, Category="PowerUp")
    float RotationSpeed = 90.f; // Degrees per second rotation

    UPROPERTY(EditAnywhere, Category="PowerUp")
    float FloatAmplitude = 20.f; // Height of floating motion

    // State variables
    bool bIsCollected = false;
    float InitialZ = 0.f;
    float LifeTime = 0.f;
    FTimerHandle RespawnTimerHandle;

    void SetPowerUpVisibility(bool bVisible);
    void OnRespawn();
    void PlayCollectionEffects();
};