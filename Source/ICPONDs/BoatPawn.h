#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BoatPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AFishingBobber;

UCLASS()
class ICPONDS_API ABoatPawn : public APawn
{
    GENERATED_BODY()

public:
    ABoatPawn();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Function to update water level from WaterManager
    UFUNCTION(BlueprintCallable, Category="Boat|Water")
    void SetWaterLevel(float NewWaterLevel) { WaterLevel = NewWaterLevel; }

    // Emergency function to reset boat position above water
    UFUNCTION(BlueprintCallable, Category="Boat|Debug")
    void ResetBoatPosition()
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Z = 100.f; // Place 1 meter above water
        SetActorLocation(NewLocation);
        
        // Reset physics velocity
        if (BoatMesh)
        {
            BoatMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
            BoatMesh->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Boat position reset to Z: %.1f"), NewLocation.Z);
    }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Boat|Fishing")
    float CastDistance = 600.f;

    UPROPERTY(EditAnywhere, Category="Boat|Fishing")
    float CastImpulse = 3500.f;

    UPROPERTY()
    AFishingBobber* ActiveBobber = nullptr;

    // Boat Components
    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* BoatMesh; // Your custom boat mesh

    UPROPERTY(VisibleAnywhere, Category="Components")
    USpringArmComponent* SpringArm; // Camera boom for third-person view

    UPROPERTY(VisibleAnywhere, Category="Components")
    UCameraComponent* Camera; // Third-person camera

    // Rowing System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Rowing")
    float OarForce = 25000.f; // Force per oar stroke

    UPROPERTY(EditAnywhere, Category="Boat|Rowing")
    float OarLeverArm = 150.f; // Distance from boat center to oar pivot (cm)

    UPROPERTY(EditAnywhere, Category="Boat|Rowing")
    float StrokeRecoveryTime = 0.8f; // Time for oar to return to neutral

    UPROPERTY(EditAnywhere, Category="Boat|Rowing")
    float StrokePowerDuration = 0.3f; // Time during which stroke applies force

    // Camera System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float CameraShakeIntensity = 2.f; // How much camera shakes during rowing

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float CameraFollowSpeed = 3.f; // How smoothly camera follows boat movement

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float MaxSpeed = 800.f; // Reduced for rowing (cm/s)

    // Enhanced Water Physics
    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float WaterLevel = 0.f;

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float BuoyancyForce = 50000.f; // Increased for stronger floating

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float WaterDensity = 1.2f;

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float SubmersionDepth = 80.f; // Reduced for more responsive buoyancy

    // Rowing state variables
    float LeftOarInput = 0.f;
    float RightOarInput = 0.f;
    float LeftOarStrokeTime = 0.f;
    float RightOarStrokeTime = 0.f;
    bool bLeftOarActive = false;
    bool bRightOarActive = false;
    float LastDebugTime = 0.f; // For debug logging

    // Input functions
    void RowLeftOar();
    void RowRightOar();
    void StartFish();
    void StopFish();

    // Physics functions
    void ApplyWaterDrag(float DeltaTime);
    void ApplyBuoyancy(float DeltaTime);
    void ApplyRowingForces(float DeltaTime);
    void UpdateOarStrokes(float DeltaTime);
    void UpdateCameraDynamics(float DeltaTime);
};
