#include "HW07GameMode.h"
#include "HW07Pawn.h"
#include "HW07PlayerController.h"

AHW07GameMode::AHW07GameMode()
{
	DefaultPawnClass = AHW07Pawn::StaticClass();
	PlayerControllerClass = AHW07PlayerController::StaticClass();
}