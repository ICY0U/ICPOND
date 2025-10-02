#include "PondGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "BoatPawn.h"

APondGameModeBase::APondGameModeBase()
{
    DefaultPawnClass = ABoatPawn::StaticClass();
}
