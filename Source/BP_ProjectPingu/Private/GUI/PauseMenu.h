// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void PlayButtonClicked();

	UFUNCTION()
	void OptionButtonClicked();

	UFUNCTION()
	void MainMenuButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* OptionButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton = nullptr;

private:
	const FName MAIN_MENU_NAME = FName(TEXT("/Script/Engine.World'/Game/Maps/MainMenu_Code.MainMenu_Code'"));
	const FName OPTION_MENU_NAME = FName(TEXT("/Script/Engine.World'/Game/Maps/OptionMenu_Code.OptionMenu_Code'"));

};
