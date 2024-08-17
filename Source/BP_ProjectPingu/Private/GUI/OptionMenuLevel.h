// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "OptionMenuLevel.generated.h"

/**
 * 
 */
UCLASS()
class AOptionMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	// Constructor
	AOptionMenuLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Option Menu Object
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UOptionMenu> OptionMenuObject;

	// Option Menu
	UPROPERTY()
	class UOptionMenu* OptionMenu;

private:
	const FString OBJECT_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_OptionsMenu_Code"));


};
