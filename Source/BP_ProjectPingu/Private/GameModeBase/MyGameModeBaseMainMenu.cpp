// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase/MyGameModeBaseMainMenu.h"
#include "GUI/MainMenu.h"
#include "Player/InputController.h"

// Constructor for the Main Menu GameModeBase
AMyGameModeBaseMainMenu::AMyGameModeBaseMainMenu()
{
	HUDClass = UMainMenu::StaticClass();
	PlayerControllerClass = AInputController::StaticClass();
}
