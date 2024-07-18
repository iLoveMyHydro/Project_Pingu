// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase/MyGameModeBaseMainMenu.h"

#include "HUD/MainMenuHUD.h"

AMyGameModeBaseMainMenu::AMyGameModeBaseMainMenu()
{
	HUDClass = AMainMenuHUD::StaticClass();
}
