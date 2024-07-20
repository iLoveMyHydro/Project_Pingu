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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UOptionMenu> OptionMenuObject;

	UPROPERTY()
	class UOptionMenu* OptionMenu;
};
