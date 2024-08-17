// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CreditsMenu.generated.h"

/**
 * 
 */
UCLASS()
class UCreditsMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// Can set the Visibility of the Credits Menu
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

private:
	// Native Construct 
	virtual void NativeConstruct() override;

	// Main Menu Button Clicked
	UFUNCTION()
	void MainMenuButtonClicked();

	// Button
	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton = nullptr;

	const FName MAIN_MENU_NAME = FName(TEXT("/Game/Maps/MainMenu_Code"));

	const FString MAIN_MENU_LEVEL_NAME = FString(TEXT("MainMenu_Code"));
};
