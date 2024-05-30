// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 *
 */
UCLASS()
class BP_PROJECTPINGU_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	const FName FIRST_LEVEL_NAME = TEXT("Project_Pingu");
	const FString QUIT_ORDER = TEXT("quit");

	virtual void NativeConstruct() override;

	UFUNCTION()
		void PlayButtonClicked();
	UFUNCTION()
		void QuitButtonClicked();

	UPROPERTY(meta = (BindWidget))
		class UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

};
