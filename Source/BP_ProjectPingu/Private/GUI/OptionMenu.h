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
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void FullscreenBoxClicked(bool bIsChecked);

	UFUNCTION()
	void VsyncBoxClicked(bool bIsChecked);

	UFUNCTION()
	void MainMenuButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* FullscreenCheckBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* VsyncCheckBox = nullptr;

private:
	const FName MAIN_MENU_NAME = FName(TEXT("/Game/Maps/MainMenu_Code"));

	const FString MAIN_MENU_LEVEL_NAME = FString(TEXT("MainMenu_Code"));
};
