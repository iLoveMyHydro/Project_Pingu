// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/NormalStateAI.h"

// Enters the State
void NormalStateAI::Enter()
{
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Green, FString::Printf(TEXT("Entering State %s"), *Name));
}

// called every frame
void NormalStateAI::Tick(float A_DeltaTime)
{
}

// Exits the State
void NormalStateAI::Exit()
{
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Red, FString::Printf(TEXT("Exiting State %s"), *Name));
}
