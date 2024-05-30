// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuLevel.generated.h"

/**
 * 
 */
UCLASS()
class BP_PROJECTPINGU_API AMainMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainMenu> MainMenuObject;

	UPROPERTY()
		class UMainMenu* MainMenu;
	
};
