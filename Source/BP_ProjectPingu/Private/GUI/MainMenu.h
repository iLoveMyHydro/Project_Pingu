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

public:
	// Constructor
	UMainMenu(const FObjectInitializer& ObjectInitializer);

private:
	// Native Constructor
	virtual void NativeConstruct() override;

	// Play Button Clicked
	UFUNCTION()
	void PlayButtonClicked();

	// Option Button Clicked
	UFUNCTION()
	void OptionButtonClicked();

	// Credits Menu Clicked
	UFUNCTION()
	void CreditsButtonClicked();

	// Quit Button Clicked
	UFUNCTION()
	void QuitButtonClicked();

	// Enable Buttons
	UFUNCTION()
	void EnableButtons(bool Enable);

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* OptionButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreditsButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton = nullptr;

	UPROPERTY()
	TSubclassOf<class UOptionMenu> OptionMenuObject;

	UPROPERTY()
	TSubclassOf<class UCreditsMenu> CreditsMenuObject;

	UPROPERTY()
	class UOptionMenu* OptionMenu = nullptr;

	UPROPERTY()
	class UCreditsMenu* CreditsMenu = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Button Disable Time", Category = "UI")
	float ButtonDisableTime = 1;

	UPROPERTY(EditAnywhere, DisplayName = "Button Disable Timer Handle", Category = "UI")
	FTimerHandle ButtonDisableTimerHandle;

	const FName LEVEL_NAME = FName(TEXT("/Game/Maps/First_Level"));
	const FName OPTION_LEVEL_NAME = FName(TEXT("/Game/Maps/OptionMenu_Code"));
	const FName CREDITS_LEVEL_NAME = FName(TEXT("/Game/Maps/CreditsMenu_Code"));

	const FString OPTION_MENU_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_OptionsMenu_Code"));
	const FString CREDITS_MENU_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_CreditsMenu_Code"));
};
