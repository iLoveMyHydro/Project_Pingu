// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/CreditsMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UCreditsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	//Binding the Methods to the UI Events
	MainMenuButton->OnClicked.AddDynamic(this, &UCreditsMenu::MainMenuButtonClicked);
}

void UCreditsMenu::MainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_NAME);
}
