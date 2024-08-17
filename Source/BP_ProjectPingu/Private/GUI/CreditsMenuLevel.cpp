// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/CreditsMenuLevel.h"
#include "BP_ProjectPingu/Private/GUI/CreditsMenu.h"
#include "Blueprint/UserWidget.h"

// Constructor
ACreditsMenuLevel::ACreditsMenuLevel()
{
	CreditsMenuObject = ConstructorHelpers::FClassFinder<UCreditsMenu>(*OBJECT_PATH).Class;
}

// Called when the game starts or when spawned
void ACreditsMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	if (CreditsMenuObject)
	{
		CreditsMenu = CreateWidget<UCreditsMenu>(GetWorld(), CreditsMenuObject);
		if (CreditsMenu)
		{
			CreditsMenu->AddToViewport();
		}
	}
}
