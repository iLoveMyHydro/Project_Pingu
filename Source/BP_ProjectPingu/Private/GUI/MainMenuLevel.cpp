// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/MainMenuLevel.h"
#include "MainMenu.h"
#include "Blueprint/UserWidget.h"

void AMainMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuObject)
	{
		MainMenu = CreateWidget<UMainMenu>(GetWorld(), MainMenuObject);
		if (MainMenu)
		{
			MainMenu->AddToViewport();
		}
	}
}
