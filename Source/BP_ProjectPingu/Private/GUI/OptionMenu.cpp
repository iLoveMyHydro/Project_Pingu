// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/OptionMenu.h"

#include "Components/CheckBox.h"
#include "Components/StackBox.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

//Audio necessities
#include "Player/InputController.h"

void UOptionMenu::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	MainMenuButton->SetVisibility(InVisibility);
	FullscreenCheckBox->SetVisibility(InVisibility);
	VsyncCheckBox->SetVisibility(InVisibility);
}

void UOptionMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	//Binding
	MainMenuButton->OnClicked.AddDynamic(this, &UOptionMenu::MainMenuButtonClicked);
	FullscreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UOptionMenu::FullscreenBoxClicked);
	VsyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UOptionMenu::VsyncBoxClicked);

}

void UOptionMenu::FullscreenBoxClicked(bool bIsChecked)
{
	UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	auto FullscreenMode = bIsChecked ? EWindowMode::Type::Fullscreen : EWindowMode::Type::Windowed;
	Settings->SetFullscreenMode(FullscreenMode);
	Settings->ApplyResolutionSettings(false);
	Settings->SaveSettings();
}

void UOptionMenu::VsyncBoxClicked(bool bIsChecked)
{
	UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	if(bIsChecked)
	{
		Settings->SetVSyncEnabled(true);
		Settings->SetFrameRateLimit(60);
	}
	else
	{
		Settings->SetVSyncEnabled(false);
	}
	Settings->ApplySettings(true);
}

void UOptionMenu::MainMenuButtonClicked()
{
	//Audio
	auto* PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Fatal, TEXT("PlayerController returned Nullpointer on button click!"));
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
