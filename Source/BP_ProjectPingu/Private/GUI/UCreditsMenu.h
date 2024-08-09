// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UCreditsMenu.generated.h"

/**
 * 
 */
UCLASS()
class UUCreditsMenu : public UUserWidget
{
	GENERATED_BODY()

private:

	virtual void NativeConstruct() override;


	UFUNCTION()
	void MainMenuButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton = nullptr;

	const FName MAIN_MENU_NAME = FName(TEXT("/Script/Engine.World'/Game/Maps/MainMenu_Code.MainMenu_Code'"));
};
