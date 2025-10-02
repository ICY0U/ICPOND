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

    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* BoatMesh;

    UPROPERTY(VisibleAnywhere, Category="Components")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, Category="Components")
    UCameraComponent* Camera;

    // Movement
    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float MaxThrust = 45000.f;

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float TurnTorque = 150000.f;

    UPROPERTY(EditAnywhere, Category="Boat|Movement")
    float MaxSpeed = 1200.f; // cm/s

    // Enhanced Water Physics
    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float WaterLevel = 0.f;

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float BuoyancyForce = 50000.f; // Increased for stronger floating

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float WaterDensity = 1.2f;

    UPROPERTY(EditAnywhere, Category="Boat|Water Physics")
    float SubmersionDepth = 80.f; // Reduced for more responsive buoyancy

    float ThrottleInput = 0.f;
    float SteeringInput = 0.f;
    float LastDebugTime = 0.f; // For debug logging

    void MoveForward(float Value);
    void MoveRight(float Value);
    void StartFish();
    void StopFish();

    void ApplyWaterDrag(float DeltaTime);
    void ApplyBuoyancy(float DeltaTime);
};
