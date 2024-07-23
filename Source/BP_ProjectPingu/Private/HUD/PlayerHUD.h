// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void SetIceSpikeAmount(int CurrentIceSpike, int MaxIceSpike);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHorizontalBox* HorizontalBox = nullptr;

	UPROPERTY(EditAnywhere, meta = (BinndWidget))
	class UImage* LifeImage = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* HealthOne = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* HealthTwo = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* HealthThree = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* IceSpikeText = nullptr;

private:
	const FString PLAYER_HUD_PATH = FString(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/HUD/C++/WBP_PlayerHUD_Code'"));

};
