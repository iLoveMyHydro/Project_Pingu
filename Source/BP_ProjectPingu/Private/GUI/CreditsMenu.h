// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsMenu.generated.h"

/**
 * 
 */
UCLASS()
class UCreditsMenu : public UUserWidget
{
	GENERATED_BODY()

private:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void MainMenuButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton = nullptr;

	const FName MAIN_MENU_NAME = FName(TEXT("/Game/Maps/MainMenu_Code"));
};
