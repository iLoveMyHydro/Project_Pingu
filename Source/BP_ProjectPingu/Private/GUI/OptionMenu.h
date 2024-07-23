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
	const FName MAIN_MENU_NAME = FName(TEXT("/Script/Engine.World'/Game/Maps/MainMenu_Code.MainMenu_Code'"));

};
