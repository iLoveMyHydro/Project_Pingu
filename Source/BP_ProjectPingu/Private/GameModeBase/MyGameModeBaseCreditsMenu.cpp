// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase/MyGameModeBaseCreditsMenu.h"
#include "GUI/CreditsMenu.h"
#include "Player/InputController.h"

AMyGameModeBaseCreditsMenu::AMyGameModeBaseCreditsMenu()
{
	HUDClass = UCreditsMenu::StaticClass();
	PlayerControllerClass = AInputController::StaticClass();
}
