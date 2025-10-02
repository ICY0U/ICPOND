#include "PondTestSpawner.h"
#include "SimpleWaterPlane.h"
#include "IslandMarker.h"
#include "CurrentVolume.h"
#include "WaterManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TextRenderComponent.h"

APondTestSpawner::APondTestSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void APondTestSpawner::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (!World) return;

    // Spawn water plane at origin
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    World->SpawnActor<ASimpleWaterPlane>(ASimpleWaterPlane::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

    // Spawn Water Manager for enhanced water physics
    AWaterManager* WaterManager = World->SpawnActor<AWaterManager>(AWaterManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);
    if (WaterManager)
    {
        WaterManager->WaterLevel = 0.f;
        WaterManager->WaveAmplitude = 8.f;
        WaterManager->WaveFrequency = 1.2f;
        WaterManager->WaveSpeed = 1.5f;
        UE_LOG(LogTemp, Log, TEXT("Water Manager spawned with enhanced wave physics"));
    }

    // Spawn islands around a ring
    for (int32 i = 0; i < NumIslands; ++i)
    {
        float Angle = (360.f / NumIslands) * i;
        FVector Pos = FVector(IslandRingRadius, 0.f, 0.f).RotateAngleAxis(Angle, FVector::UpVector);
        FRotator Rot = FRotator::ZeroRotator;
        AIslandMarker* Island = World->SpawnActor<AIslandMarker>(AIslandMarker::StaticClass(), Pos, Rot, Params);
        if (Island)
        {
            Island->IslandIndex = i + 1;
            if (Island->Label)
            {
                Island->Label->SetText(FText::FromString(FString::Printf(TEXT("Island %d"), i+1)));
            }
        }
    }

    // Place a ring of current volumes to create a gentle clockwise flow
    const int32 CurrentVolumes = 12;
    for (int32 i = 0; i < CurrentVolumes; ++i)
    {
        float Angle = (360.f / CurrentVolumes) * i;
        FVector Center = FVector(IslandRingRadius * 0.8f, 0.f, 0.f).RotateAngleAxis(Angle, FVector::UpVector);
        FRotator Rot = FRotator::ZeroRotator;

        ACurrentVolume* Curr = World->SpawnActor<ACurrentVolume>(ACurrentVolume::StaticClass(), Center + FVector(0,0,CurrentRingHeight), Rot, Params);
        if (Curr)
        {
            FVector TangentDir = FVector(1.f, 0.f, 0.f).RotateAngleAxis(Angle + 90.f, FVector::UpVector);
            Curr->FlowDirection = TangentDir.GetSafeNormal();
            Curr->FlowStrength = CurrentStrength;
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Enhanced Pond Test Environment Created: %d islands, %d current volumes, water manager with waves"), NumIslands, CurrentVolumes);
}
