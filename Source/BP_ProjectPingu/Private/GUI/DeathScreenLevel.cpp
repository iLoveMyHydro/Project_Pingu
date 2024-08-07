// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/DeathScreenLevel.h"
#include "GUI/DeathScreen.h"
#include "Blueprint/UserWidget.h"

void ADeathScreenLevel::BeginPlay()
{
	Super::BeginPlay();

	if (DeathScreenObject)
	{
		DeathScreen = CreateWidget<UDeathScreen>(GetWorld(), DeathScreenObject);
		if (DeathScreen)
		{
			DeathScreen->AddToViewport();
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
