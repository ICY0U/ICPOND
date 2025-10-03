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

    // Movement System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float MaxThrust = 45000.f; // Forward/backward thrust force

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float TurnTorque = 150000.f; // Turning force

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float MaxSpeed = 1200.f; // Maximum boat speed (cm/s)

    // Camera System Properties
    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float CameraShakeIntensity = 1.f; // How much camera shakes during movement

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float CameraFollowSpeed = 3.f; // How smoothly camera follows boat movement

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float MouseSensitivityX = 1.f; // Horizontal mouse sensitivity

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float MouseSensitivityY = 0.7f; // Vertical mouse sensitivity

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float MinPitchAngle = -80.f; // Maximum upward camera angle

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    float MaxPitchAngle = 10.f; // Maximum downward camera angle

    UPROPERTY(EditAnywhere, Category="Boat|Camera")
    bool bEnableMouseControl = true; // Toggle mouse camera control

    // Enhanced Water Physics
    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float WaterLevel = 0.f;

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float BuoyancyForce = 50000.f; // Increased for stronger floating

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float WaterDensity = 1.2f;

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float SubmersionDepth = 80.f; // Reduced for more responsive buoyancy

    // Movement state variables
    float ThrottleInput = 0.f;
    float SteeringInput = 0.f;
    float CameraYawInput = 0.f; // Mouse X input accumulation
    float CameraPitchInput = 0.f; // Mouse Y input accumulation
    float LastDebugTime = 0.f; // For debug logging

    // Input functions
    void MoveForward(float Value);
    void MoveRight(float Value);
    void MouseX(float Value);
    void MouseY(float Value);
    void StartFish();
    void StopFish();

    // Physics functions
    void ApplyWaterDrag(float DeltaTime);
    void ApplyBuoyancy(float DeltaTime);
    void UpdateCameraDynamics(float DeltaTime);
};
