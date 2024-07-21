// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/PlayerHUD.h"
#include "GUI/LifeImage.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

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
		for (int i = 0; i < CurrentLife; i++)
		{
			//LifeImageObject = ConstructorHelpers::FClassFinder<UPlayerHUD>(*PLAYER_HUD_PATH).Class;


			//LifeImage = CreateWidget<ULifeImage>(HorizontalBox, LifeImageObject, TEXT("Life Image"));
			//HorizontalBox->AddChild(LifeImage);
		}
	}
}

void UPlayerHUD::SetIceSpikeAmount(int CurrentIceSpike, int MaxIceSpike)
{
	if (CurrentIceSpike == MaxIceSpike)
	{
		FText currentIceSpike = FText::FromString(FString::FromInt(MaxIceSpike));
		IceSpikeText->SetText(currentIceSpike);
	}
	else
	{
		FText currentIceSpike = FText::FromString(FString::FromInt(CurrentIceSpike));
		IceSpikeText->SetText(currentIceSpike);
	}
}
