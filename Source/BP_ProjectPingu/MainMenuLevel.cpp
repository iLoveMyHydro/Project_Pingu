// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuLevel.h"
#include "MainMenu.h"

void AMainMenuLevel::BeginPlay()
{
	if (MainMenuObject)
	{
		MainMenu = CreateWidget<UMainMenu>(GetWorld(), MainMenuObject);
		if (MainMenu)
		{
			MainMenu->AddToViewport();
		}
	}
}