// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "PauseMenuLevel.generated.h"

/**
 * 
 */
UCLASS()
class APauseMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	APauseMenuLevel();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPauseMenu> PauseMenuObejct;

	UPROPERTY()
	class UPauseMenu* PauseMenu;

private:
	const FString OBJECT_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_PauseMenu_Code"));


};
