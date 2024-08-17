// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/DeathScreen.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDeathScreen::SetDeathScreen(bool bIsScreenOn)
{
	// If the bool is on the Screen is shown else not
	if(bIsScreenOn)
	{
		Background->SetVisibility(ESlateVisibility::Visible);
		DeathText->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Background->SetVisibility(ESlateVisibility::Hidden);
		DeathText->SetVisibility(ESlateVisibility::Hidden);
	}
}
