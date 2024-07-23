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

	UFUNCTION()
	void OptionButtonClicked();

	UFUNCTION()
	void CreditsButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* OptionButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreditsButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton = nullptr;

	const FName LEVEL_NAME = FName(TEXT("/Script/Engine.World'/Game/Maps/Project_Pingu.Project_Pingu'"));
	const FName OPTION_LEVEL_NAME = FName(TEXT(""));
	const FName CREDITS_LEVEL_NAME = FName(TEXT(""));
};
