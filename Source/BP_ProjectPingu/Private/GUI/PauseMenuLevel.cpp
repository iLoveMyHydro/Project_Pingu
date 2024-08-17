// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/PauseMenuLevel.h"
#include "GUI/PauseMenu.h"
#include "Blueprint/UserWidget.h"

// Constructor
APauseMenuLevel::APauseMenuLevel()
{
	PauseMenuObejct = ConstructorHelpers::FClassFinder<UPauseMenu>(*OBJECT_PATH).Class;
}

// Called when the game starts or when spawned
void APauseMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	if (PauseMenuObejct)
	{
		PauseMenu = CreateWidget<UPauseMenu>(GetWorld(), PauseMenuObejct);
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();
		}
	}
}
