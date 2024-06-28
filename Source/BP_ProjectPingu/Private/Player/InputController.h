// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "InputController.generated.h"

/**
 * 
 */
UCLASS()
class AInputController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Contex", Category = "Input") )
	UInputMappingContext* InputMappingContext = nullptr;

	virtual void BeginPlay() override;
};
