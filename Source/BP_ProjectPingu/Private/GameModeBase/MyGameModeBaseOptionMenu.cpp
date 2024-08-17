// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase/MyGameModeBaseOptionMenu.h"
#include "Player/InputController.h"
#include "GUI/OptionMenu.h"

// Constructor for the Option Menu GameModeBase
AMyGameModeBaseOptionMenu::AMyGameModeBaseOptionMenu()
{
	HUDClass = UOptionMenu::StaticClass();
	PlayerControllerClass = AInputController::StaticClass();
}
