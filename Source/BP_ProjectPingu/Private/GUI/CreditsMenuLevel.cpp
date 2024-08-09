// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/CreditsMenuLevel.h"
#include "BP_ProjectPingu/Private/GUI/UCreditsMenu.h"
#include "Blueprint/UserWidget.h"

ACreditsMenuLevel::ACreditsMenuLevel()
{
	CreditsMenuObject = ConstructorHelpers::FClassFinder<UUCreditsMenu>(*OBJECT_PATH).Class;

}

void ACreditsMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	if (CreditsMenuObject)
	{
		CreditsMenu = CreateWidget<UUCreditsMenu>(GetWorld(), CreditsMenuObject);
		if (CreditsMenu)
		{
			CreditsMenu->AddToViewport();
		}
	}
}
