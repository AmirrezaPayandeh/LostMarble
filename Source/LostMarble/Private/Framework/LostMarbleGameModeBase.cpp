// Copyright Amirreza Payandeh. All Rights Reserved.

#include "Framework/LostMarbleGameModeBase.h"
#include "Character/MarbleBall.h"
#include "Character/MarbleBallController.h"

ALostMarbleGameModeBase::ALostMarbleGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = false;

	DefaultPawnClass = AMarbleBall::StaticClass();
	PlayerControllerClass = AMarbleBallController::StaticClass();
}