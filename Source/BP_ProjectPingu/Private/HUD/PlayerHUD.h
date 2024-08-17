// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class APinguCharacter;

/**
 * 
 */
UCLASS()
class UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	// Sets the Life UI
	void SetLifeAmount(int CurrentLife, int MaxLife);

	// Sets the Ice Spike UI
	void SetIceSpikeAmount(int CurrentIceSpike, int MaxIceSpike);

private:
	// Horizontal Box
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHorizontalBox* HorizontalBox = nullptr;

	// Life Image
	UPROPERTY(EditAnywhere, meta = (BinndWidget))
	class UImage* LifeImage = nullptr;

	// Canvas Panel
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* HealthOne = nullptr;

	// Canvas Panel
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* HealthTwo = nullptr;

	// Canvas Panel
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* HealthThree = nullptr;

	// Ice Spike Text
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* IceSpikeText = nullptr;

	// Ice Spike Image
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* IceSpike = nullptr;

	// Ice Spike Max Text
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* IceSpikeMaxText = nullptr;

	const FString PLAYER_HUD_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_PlayerHUD_Code"));

	APinguCharacter* PinguCharacter = nullptr;

};
