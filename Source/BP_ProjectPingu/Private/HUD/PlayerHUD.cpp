// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PinguCharacter.h"


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
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn())
	{
		PinguCharacter = Cast<APinguCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	}

	if(PinguCharacter->GetGotIceSpikes())
	{
		IceSpikeText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		IceSpike->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		IceSpikeMaxText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

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
	else if(PinguCharacter == nullptr)
	{
		return;
	}
	else
	{
		IceSpikeText->SetVisibility(ESlateVisibility::Hidden);
		IceSpike->SetVisibility(ESlateVisibility::Hidden);
		IceSpikeMaxText->SetVisibility(ESlateVisibility::Hidden);
	}
}
