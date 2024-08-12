// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/PauseMenu.h"
#include "OptionMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/InputController.h"
#include "Player/PinguCharacter.h"

void UPauseMenu::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	Background->SetVisibility(InVisibility);
	MainMenuButton->SetVisibility(InVisibility);
	OptionButton->SetVisibility(InVisibility);
	QuitButton->SetVisibility(InVisibility);
	PlayButton->SetVisibility(InVisibility);
}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	//Binding
	PlayButton->OnClicked.AddDynamic(this, &UPauseMenu::PlayButtonClicked);
	OptionButton->OnClicked.AddDynamic(this, &UPauseMenu::OptionButtonClicked);
	MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::MainMenuButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::QuitButtonClicked);

}

void UPauseMenu::PlayButtonClicked()
{
	AInputController* const PlayerController = Cast<AInputController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if(PlayerController != nullptr)
	{
		PlayerController->SetPause(false);
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
	SetVisibility(ESlateVisibility::Hidden);

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn())
	{
		Character = Cast<APinguCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	}
	Controller = Cast<AInputController>(Character->GetController());
	Controller->PlayLevelTheme();

}

void UPauseMenu::OptionButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), OPTION_MENU_NAME);
	SetVisibility(ESlateVisibility::Hidden);

}

void UPauseMenu::MainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_NAME);
	SetVisibility(ESlateVisibility::Hidden);

}

void UPauseMenu::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}