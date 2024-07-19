// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void PlayButtonClicked();
	void OptionButtonClicked();
	void CreditsButtonClicked();
	void QuitButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

private:
	const FName LEVEL_NAME = FName(TEXT("/Script/Engine.World'/Game/Maps/Project_Pingu.Project_Pingu'"));
	const FName OPTION_LEVEL_NAME = FName(TEXT(""));
	const FName CREDITS_LEVEL_NAME = FName(TEXT(""));
};
