// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/UCreditsMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUCreditsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	//Binding the Methods to the UI Events
	MainMenuButton->OnClicked.AddDynamic(this, &UUCreditsMenu::MainMenuButtonClicked);
}

void UUCreditsMenu::MainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_NAME);
}
