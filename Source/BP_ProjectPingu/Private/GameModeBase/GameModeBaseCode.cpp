// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase/GameModeBaseCode.h"
#include "Player/PinguCharacter.h"
#include "Player/InputController.h"

AGameModeBaseCode::AGameModeBaseCode()
{
	DefaultPawnClass = APinguCharacter::StaticClass();
	PlayerControllerClass = AInputController::StaticClass();
}
