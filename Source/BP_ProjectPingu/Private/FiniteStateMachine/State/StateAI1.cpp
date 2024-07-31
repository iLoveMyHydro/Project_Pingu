// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/StateAI1.h"

void StateAI1::Enter()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Green, FString::Printf(TEXT("Entering State %s"), *Name));
}

void StateAI1::Tick(float A_DeltaTime)
{
	
}

void StateAI1::Exit()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Red, FString::Printf(TEXT("Exiting State %s"), *Name));

}
