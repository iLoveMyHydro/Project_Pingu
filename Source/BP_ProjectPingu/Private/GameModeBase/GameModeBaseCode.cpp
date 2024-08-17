// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase/GameModeBaseCode.h"

#include "GUI/PauseMenu.h"
#include "Player/PinguCharacter.h"
#include "Player/InputController.h"

// Constructor for the GameModeBose
AGameModeBaseCode::AGameModeBaseCode()
{
	DefaultPawnClass = APinguCharacter::StaticClass();
	PlayerControllerClass = AInputController::StaticClass();
	HUDClass = UPauseMenu::StaticClass();
}