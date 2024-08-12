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
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

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

	UPROPERTY(meta = (BindWidget))
	class UImage* Background = nullptr;

private:
	const FName MAIN_MENU_NAME = FName(TEXT("/Game/Maps/MainMenu_Code"));
	const FName OPTION_MENU_NAME = FName(TEXT("/Game/Maps/OptionMenu_Code"));

	class AInputController* Controller = nullptr;
	APinguCharacter* Character = nullptr;

};
