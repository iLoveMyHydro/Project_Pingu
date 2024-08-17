// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/MainMenuLevel.h"
#include "MainMenu.h"
#include "Blueprint/UserWidget.h"

// Constructor
AMainMenuLevel::AMainMenuLevel()
{
	MainMenuObject = ConstructorHelpers::FClassFinder<UMainMenu>(*OBJECT_PATH).Class;
}

// Called when the game starts or when spawned
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
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Menu Loaded!"));

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Object Loaded!"));
	}
}
