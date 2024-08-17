// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuLevel.generated.h"

/**
 * 
 */
UCLASS()
class AMainMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()

	// Constructor
	AMainMenuLevel();

protected:
	virtual void BeginPlay() override;

	// Main Menu Object
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainMenu> MainMenuObject;

	// Main Menu
	UPROPERTY()
	class UMainMenu* MainMenu;


private:
	const FString OBJECT_PATH = FString(TEXT("WidgetBlueprint'/Game/Blueprint/HUD/C++/WBP_MainMenu_Code'"));

};
