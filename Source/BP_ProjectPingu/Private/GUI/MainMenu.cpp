// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

//Audio necessities
#include "Player/InputController.h"


void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	//Binding the Methods to the UI Events
	PlayButton->OnClicked.AddDynamic(this, &UMainMenu::PlayButtonClicked);
	OptionButton->OnClicked.AddDynamic(this, &UMainMenu::OptionButtonClicked);
	CreditsButton->OnClicked.AddDynamic(this, &UMainMenu::CreditsButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonClicked);
}

void UMainMenu::PlayButtonClicked()
{
	//Audio
	auto* PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController returned Nullpointer on button click!"));
		return;
	}
	PlayerController->PlayUIConfirmSound();

	UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME);
}

void UMainMenu::OptionButtonClicked()
{
	//Audio
	auto* PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController returned Nullpointer on button click!"));
		return;
	}
	PlayerController->PlayUIConfirmSound();

	UGameplayStatics::OpenLevel(GetWorld(), OPTION_LEVEL_NAME);
}

void UMainMenu::CreditsButtonClicked()
{
	//Audio
	auto* PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController returned Nullpointer on button click!"));
		return;
	}
	PlayerController->PlayUIConfirmSound();

	UGameplayStatics::OpenLevel(GetWorld(), CREDITS_LEVEL_NAME);
}

void UMainMenu::QuitButtonClicked()
{
	//Audio
	auto* PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController returned Nullpointer on button click!"));
		return;
	}
	PlayerController->PlayUIConfirmSound();
	
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
