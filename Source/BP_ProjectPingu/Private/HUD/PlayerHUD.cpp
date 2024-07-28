// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void UPlayerHUD::SetLifeAmount(int CurrentLife, int MaxLife)
{
	if(CurrentLife == 2)
	{
		HealthThree->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (CurrentLife == 1)
	{
		HealthThree->SetVisibility(ESlateVisibility::Hidden);
		HealthTwo->SetVisibility(ESlateVisibility::Hidden);
	}
	else if(CurrentLife == 3)
	{
		HealthThree->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		HealthTwo->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		HealthOne->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

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
