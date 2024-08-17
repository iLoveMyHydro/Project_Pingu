// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/PinguMapLevel.h"

void APinguMapLevel::BeginPlay()
{
	Super::BeginPlay();

	// Sets the Input Mode
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
}
