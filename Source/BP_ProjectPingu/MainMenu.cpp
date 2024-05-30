// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	//Binding the Methods to the UI Events
	PlayButton->OnClicked.AddDynamic(this, &UMainMenu::PlayButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonClicked);
}

void UMainMenu::PlayButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FIRST_LEVEL_NAME);
}

void UMainMenu::QuitButtonClicked()
{
	GetWorld()->GetGameViewport()->ConsoleCommand(QUIT_ORDER);
}
