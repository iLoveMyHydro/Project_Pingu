// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "DeathScreenLevel.generated.h"

/**
 * 
 */
UCLASS()
class ADeathScreenLevel : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDeathScreen> DeathScreenObject;

	UPROPERTY()
	class UDeathScreen* DeathScreen;


private:
	const FString OBJECT_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_DeathScreen"));
};
