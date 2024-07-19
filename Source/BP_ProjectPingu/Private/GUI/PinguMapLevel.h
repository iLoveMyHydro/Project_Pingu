// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "PinguMapLevel.generated.h"

/**
 * 
 */
UCLASS()
class APinguMapLevel : public ALevelScriptActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
};
