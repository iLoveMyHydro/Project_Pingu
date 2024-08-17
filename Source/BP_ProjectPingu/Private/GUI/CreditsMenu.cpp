// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/CreditsMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

//Audio necessities
#include "Player/InputController.h"

// Sets the Visibility of the MainMenuButton
void UCreditsMenu::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	MainMenuButton->SetVisibility(InVisibility);
}

// Native Construct of the CreditsMenu
void UCreditsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Sets the Input Mode
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	//Binding the Methods to the UI Events
	MainMenuButton->OnClicked.AddDynamic(this, &UCreditsMenu::MainMenuButtonClicked);
}

// MainMenuButton Clicked
void UCreditsMenu::MainMenuButtonClicked()
{
	//Audio
	auto* PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController returned Nullpointer on button click!"));
		return;
	}
	PlayerController->PlayUIConfirmSound();

	if (GetWorld())
	{
		FString MapName = GetWorld()->GetMapName();
		MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		if (MapName == MAIN_MENU_LEVEL_NAME)
		{
			SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Map name: %s"), *MapName);
			UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_NAME);
		}
	}
}
