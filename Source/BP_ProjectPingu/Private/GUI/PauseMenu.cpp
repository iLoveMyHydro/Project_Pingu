// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/PauseMenu.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/InputController.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPauseMenu::PlayButtonClicked()
{
	AInputController* const PlayerController = Cast<AInputController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if(PlayerController != nullptr)
	{
		PlayerController->SetPause(false);
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
		RemoveFromParent();
	}
}

void UPauseMenu::OptionButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_NAME);
}

void UPauseMenu::MainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_NAME);
}

void UPauseMenu::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UPauseMenu::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	Background->SetVisibility(InVisibility);
	OptionButton->SetVisibility(InVisibility);
	MainMenuButton->SetVisibility(InVisibility);
	PlayButton->SetVisibility(InVisibility);
	QuitButton->SetVisibility(InVisibility);
}
