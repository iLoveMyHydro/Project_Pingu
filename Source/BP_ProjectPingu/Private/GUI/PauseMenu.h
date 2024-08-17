// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class APinguCharacter;
/**
 * 
 */
UCLASS()
class UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// Sets the Visibility 
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

private:
	// Native Constructor
	virtual void NativeConstruct() override;

	// Play Button
	UFUNCTION()
	void PlayButtonClicked();

	// Option Button
	UFUNCTION()
	void OptionButtonClicked();

	// Main Menu Button
	UFUNCTION()
	void MainMenuButtonClicked();

	// Quit Button
	UFUNCTION()
	void QuitButtonClicked();

	// Main Menu Button
	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton = nullptr;

	// Play Button
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton = nullptr;

	// Option Button
	UPROPERTY(meta = (BindWidget))
	class UButton* OptionButton = nullptr;

	// Quit Button
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton = nullptr;

	// Background Image
	UPROPERTY(meta = (BindWidget))
	class UImage* Background = nullptr;

private:
	const FName MAIN_MENU_NAME = FName(TEXT("/Game/Maps/MainMenu_Code"));
	const FName OPTION_MENU_NAME = FName(TEXT("/Game/Maps/OptionMenu_Code"));

	class AInputController* Controller = nullptr;
	APinguCharacter* Character = nullptr;

};
