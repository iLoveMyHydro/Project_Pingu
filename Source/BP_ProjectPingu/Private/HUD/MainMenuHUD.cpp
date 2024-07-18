// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuHUD.h"
#include "Blueprint/UserWidget.h"

AMainMenuHUD::AMainMenuHUD()
{
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	auto WidgetClass = ConstructorHelpers::FClassFinder<UUserWidget>(*WIDGET_PATH).Class;
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), WidgetClass);
	Widget->AddToViewport();
}
