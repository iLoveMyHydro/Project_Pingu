// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/OptionMenuLevel.h"
#include "OptionMenu.h"
#include "Blueprint/UserWidget.h"

void AOptionMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	if (OptionMenuObject)
	{
		OptionMenu = CreateWidget<UOptionMenu>(GetWorld(), OptionMenuObject);
		if (OptionMenu)
		{
			OptionMenu->AddToViewport();
		}
	}
}
