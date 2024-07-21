// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/LifeImage.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetLifeAmount(int CurrentLife, int MaxLife);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHorizontalBox* HorizontalBox = nullptr;

	UPROPERTY()
	class ULifeImage* LifeImage = nullptr;

	UPROPERTY()
	TSubclassOf<class ULifeImage> LifeImageObject;

private:
	const FString PLAYER_HUD_PATH = FString(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/HUD/C++/WBP_PlayerHUD_Code'"));

};
