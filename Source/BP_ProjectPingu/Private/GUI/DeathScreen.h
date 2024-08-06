// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathScreen.generated.h"

/**
 * 
 */
UCLASS()
class UDeathScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDeathScreen(bool bIsScreenOn);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Background = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DeathText = nullptr;

	const FString PLAYER_HUD_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_DeathScreen_Code"));
	
};
