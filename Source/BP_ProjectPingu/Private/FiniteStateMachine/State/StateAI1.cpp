// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/StateAI1.h"

void StateAI1::Enter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf((ENTERING_STATE), name));
}

void StateAI1::Tick(float a_deltaTime)
{
	
}

void StateAI1::Exit()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf((EXIT_STATE), name));

}
