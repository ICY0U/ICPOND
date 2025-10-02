#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "IslandMarker.generated.h"

UCLASS()
class ICPONDS_API AIslandMarker : public AActor
{
    GENERATED_BODY()

public:
    AIslandMarker();

    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, Category="Components")
    UTextRenderComponent* Label;

    UPROPERTY(EditAnywhere, Category="Island")
    int32 IslandIndex = 0;
};
