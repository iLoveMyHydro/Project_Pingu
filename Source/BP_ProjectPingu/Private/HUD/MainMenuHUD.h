// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMainMenuHUD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const FString WIDGET_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.MainMenuHUD'"));

};
