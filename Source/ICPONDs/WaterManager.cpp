#include "WaterManager.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "BoatPawn.h"

AWaterManager::AWaterManager()
{
    PrimaryActorTick.bCanEverTick = true;
    SetActorLocation(FVector::ZeroVector);
}

void AWaterManager::BeginPlay()
{
    Super::BeginPlay();
    GameTime = 0.f;
    UE_LOG(LogTemp, Warning, TEXT("WaterManager BeginPlay - Water Level: %.2f, Wave Amplitude: %.2f"), WaterLevel, WaveAmplitude);
}

void AWaterManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    GameTime += DeltaTime;

    // Debug logging every 2 seconds
    static float LastLogTime = 0.f;
    if (GameTime - LastLogTime > 2.0f)
    {
        LastLogTime = GameTime;
        UE_LOG(LogTemp, Warning, TEXT("WaterManager Tick - GameTime: %.2f, WaterLevel: %.2f"), GameTime, WaterLevel);
    }

    // Update all boat pawns with current water level
    UWorld* World = GetWorld();
    if (World)
    {
        int32 BoatsUpdated = 0;
        for (TActorIterator<ABoatPawn> ActorItr(World); ActorItr; ++ActorItr)
        {
            ABoatPawn* BoatPawn = *ActorItr;
            if (BoatPawn)
            {
                // Update boat's water level with wave height at its location
                const float WaveHeight = GetWaterHeightAtLocation(BoatPawn->GetActorLocation());
                BoatPawn->SetWaterLevel(WaveHeight);
                BoatsUpdated++;
                
                // Debug first boat only
                if (BoatsUpdated == 1 && GameTime - LastLogTime > 1.9f)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Updated Boat - Location: %s, Calculated Water Height: %.2f"), 
                        *BoatPawn->GetActorLocation().ToString(), WaveHeight);
                }
            }
        }
    }
}

float AWaterManager::GetWaterHeightAtLocation(const FVector& Location) const
{
    // Calculate wave height using multiple sine waves for more realistic water
    const float Wave1 = FMath::Sin((Location.X * 0.005f) + (GameTime * WaveSpeed)) * WaveAmplitude;
    const float Wave2 = FMath::Sin((Location.Y * 0.003f) + (GameTime * WaveSpeed * 1.3f)) * WaveAmplitude * 0.7f;
    const float Wave3 = FMath::Sin(((Location.X + Location.Y) * 0.002f) + (GameTime * WaveSpeed * 0.8f)) * WaveAmplitude * 0.5f;
    
    return WaterLevel + Wave1 + Wave2 + Wave3;
}

bool AWaterManager::IsLocationUnderwater(const FVector& Location) const
{
    return Location.Z < GetWaterHeightAtLocation(Location);
}