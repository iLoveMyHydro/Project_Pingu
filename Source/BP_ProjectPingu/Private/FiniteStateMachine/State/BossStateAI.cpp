// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/BossStateAI.h"

void BossStateAI::Enter()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Green, FString::Printf(TEXT("Entering State %s"), *Name));
}

void BossStateAI::Tick(float A_DeltaTime)
{
}

void BossStateAI::Exit()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Red, FString::Printf(TEXT("Exiting State %s"), *Name));
}
