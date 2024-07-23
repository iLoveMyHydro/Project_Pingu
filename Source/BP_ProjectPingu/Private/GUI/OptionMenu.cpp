// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/OptionMenu.h"

#include "Components/CheckBox.h"
#include "Components/StackBox.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

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
	UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_NAME);
}
