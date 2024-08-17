// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/PauseMenu.h"
#include "OptionMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/InputController.h"
#include "Player/PinguCharacter.h"

// Sets the Visibility
void UPauseMenu::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	Background->SetVisibility(InVisibility);
	MainMenuButton->SetVisibility(InVisibility);
	OptionButton->SetVisibility(InVisibility);
	QuitButton->SetVisibility(InVisibility);
	PlayButton->SetVisibility(InVisibility);
}

// Native Constructor
void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	//Binding
	PlayButton->OnClicked.AddDynamic(this, &UPauseMenu::PlayButtonClicked);
	OptionButton->OnClicked.AddDynamic(this, &UPauseMenu::OptionButtonClicked);
	MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::MainMenuButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::QuitButtonClicked);

}

// Play Button Clicked
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
	Controller->UnpauseLevelTheme();
	Controller->PlayUIConfirmSound();

}

// Option Button 
void UPauseMenu::OptionButtonClicked()
{
	//Audio
	auto* PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController returned Nullpointer on button click!"));
		return;
	}
	PlayerController->PlayUIConfirmSound();

	PlayerController->OpenOptionsMenu();

	SetVisibility(ESlateVisibility::Hidden);
}

// Main Menu
void UPauseMenu::MainMenuButtonClicked()
{
	//Audio
	auto* PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController returned Nullpointer on button click!"));
		return;
	}
	PlayerController->PlayUIConfirmSound();

	UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_NAME);
	SetVisibility(ESlateVisibility::Hidden);
}

// Quit Button
void UPauseMenu::QuitButtonClicked()
{
	//Audio
	auto* PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController returned Nullpointer on button click!"));
		return;
	}
	PlayerController->PlayUIConfirmSound();
}