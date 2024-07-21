// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/PlayerHUD.h"
#include "GUI/LifeImage.h"
#include "Components/HorizontalBox.h"

void UPlayerHUD::SetLifeAmount(int CurrentLife, int MaxLife)
{
	//TODO: Set Life

	if(CurrentLife == MaxLife)
	{
		//TODO: Set Max Life in Bar
		for (int i = 0; i < MaxLife; i++)
		{
			//LifeImageObject = ConstructorHelpers::FClassFinder<UPlayerHUD>(*PLAYER_HUD_PATH).Class;


			//LifeImage = CreateWidget<ULifeImage>(HorizontalBox, LifeImageObject, TEXT("Life Image"));
			//HorizontalBox->AddChild(LifeImage);
		}
	}
	else
	{
		//TODO: Set Current Life in Bar
	}
}
