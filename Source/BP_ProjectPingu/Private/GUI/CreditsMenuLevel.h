// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CreditsMenuLevel.generated.h"

/**
 * 
 */
UCLASS()
class ACreditsMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ACreditsMenuLevel(); 


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCreditsMenu> CreditsMenuObject;

	UPROPERTY()
	class UCreditsMenu* CreditsMenu;

private:
	const FString OBJECT_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_CreditsMenu_Code"));
};
