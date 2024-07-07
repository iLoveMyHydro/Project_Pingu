// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/StateBossAI1.h"

void StateBossAI1::Enter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Entering State %s"), *Name));
}

void StateBossAI1::Tick(float DeltaTime)
{
	
}

void StateBossAI1::Exit()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Exiting Stae %s"), *Name));
}


