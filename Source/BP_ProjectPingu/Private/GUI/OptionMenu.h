// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "OptionMenu.generated.h"

/**
 * 
 */
UCLASS()
class UOptionMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// Set Visibility 
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

private:
	// Native Constructor
	virtual void NativeConstruct() override;

	// Fullscreen Button
	UFUNCTION()
	void FullscreenBoxClicked(bool bIsChecked);

	// Vsync Button
	UFUNCTION()
	void VsyncBoxClicked(bool bIsChecked);

	// Main Menu Button
	UFUNCTION()
	void MainMenuButtonClicked();

	// Main Menu Button
	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton = nullptr;

	// FullscreenBox
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* FullscreenCheckBox = nullptr;

	// Vsync Box
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* VsyncCheckBox = nullptr;

private:
	const FName MAIN_MENU_NAME = FName(TEXT("/Game/Maps/MainMenu_Code"));

	const FString MAIN_MENU_LEVEL_NAME = FString(TEXT("MainMenu_Code"));
};
