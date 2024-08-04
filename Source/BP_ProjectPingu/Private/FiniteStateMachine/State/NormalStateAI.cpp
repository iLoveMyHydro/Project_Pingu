// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/NormalStateAI.h"

void NormalStateAI::Enter()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Green, FString::Printf(TEXT("Entering State %s"), *Name));
}

void NormalStateAI::Tick(float A_DeltaTime)
{
}

void NormalStateAI::Exit()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Red, FString::Printf(TEXT("Exiting State %s"), *Name));
}
