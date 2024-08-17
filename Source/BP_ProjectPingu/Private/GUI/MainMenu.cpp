// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GUI/OptionMenu.h"
#include "GUI/CreditsMenu.h"

//Audio necessities
#include "Player/InputController.h"

// Constructor
UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	OptionMenuObject = ConstructorHelpers::FClassFinder<UOptionMenu>(*OPTION_MENU_PATH).Class;
	CreditsMenuObject = ConstructorHelpers::FClassFinder<UCreditsMenu>(*CREDITS_MENU_PATH).Class;
}

// Native Constructor
void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Set Input Mode
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	if (OptionMenuObject)
	{
		OptionMenu = CreateWidget<UOptionMenu>(this, OptionMenuObject, "Object Menu");
	}

	if (CreditsMenuObject)
	{
		CreditsMenu = CreateWidget<UCreditsMenu>(this, CreditsMenuObject, "Credits Menu");
	}

	//Binding the Methods to the UI Events
	PlayButton->OnClicked.AddDynamic(this, &UMainMenu::PlayButtonClicked);
	OptionButton->OnClicked.AddDynamic(this, &UMainMenu::OptionButtonClicked);
	CreditsButton->OnClicked.AddDynamic(this, &UMainMenu::CreditsButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonClicked);
}

// Play Button
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
	EnableButtons(false);
	GetWorld()->GetTimerManager().SetTimer(ButtonDisableTimerHandle, 
	[this]() 
	{
		EnableButtons(true);
		UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME);
		GetWorld()->GetTimerManager().ClearTimer(ButtonDisableTimerHandle);
	}, 
	ButtonDisableTime, 
	false);
	GetWorld()->GetTimerManager().ListTimers();
}

// Option Button
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

	// UGameplayStatics::OpenLevel(GetWorld(), OPTION_LEVEL_NAME);
	if (OptionMenu)
	{
		OptionMenu->SetVisibility(ESlateVisibility::Visible);
		OptionMenu->AddToViewport();
	}
}

// Credits Button
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

	// UGameplayStatics::OpenLevel(GetWorld(), CREDITS_LEVEL_NAME);

	if (CreditsMenu)
	{
		CreditsMenu->SetVisibility(ESlateVisibility::Visible);
		CreditsMenu->AddToViewport();
	}
}

// Quit Button 
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
	EnableButtons(false);
	GetWorld()->GetTimerManager().SetTimer(ButtonDisableTimerHandle, 
	[this]() 
	{
		EnableButtons(true);
		UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
		GetWorld()->GetTimerManager().ClearTimer(ButtonDisableTimerHandle);
	}, 
	ButtonDisableTime, 
	false);
}

// Enables the Buttons
void UMainMenu::EnableButtons(bool Enable)
{
	PlayButton->SetIsEnabled(Enable);
	OptionButton->SetIsEnabled(Enable);
	CreditsButton->SetIsEnabled(Enable);
	QuitButton->SetIsEnabled(Enable);
}

