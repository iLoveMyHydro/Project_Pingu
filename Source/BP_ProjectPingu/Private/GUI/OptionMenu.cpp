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
	//FullscreenCheckBox->OnCheckStateChanged
	//VsyncCheckBox->OnCheckStateChanged

}

void UOptionMenu::FullscreenBoxClicked()
{
	//UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	//auto FullscreenMode = clicked ? EWindowMode::Type::Fullscreen : EWindowMode::Type::Windowed;
	//Settings->SetFullscreenMode(FullscreenMode);
	//Settings->ApplyResolutionSettings(false);
	//Settings->SaveSettings();
}

void UOptionMenu::VsyncBoxClicked()
{
	//UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	//bool bIsVsyncMode = clicked ? Settings->SetVSyncEnabled(true) : Settings->SetVSyncEnabled(false);
	//if (bIsVsyncMode) Settings->SetVSyncEnabled(bIsVsyncMode);
	//if (bIsVsyncMode) Settings->SetFrameRateLimit(60);
	//Settings->ApplySettings(true);
}

void UOptionMenu::MainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_NAME);
}
