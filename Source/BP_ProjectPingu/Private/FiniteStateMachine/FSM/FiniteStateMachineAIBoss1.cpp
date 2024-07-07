// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/FSM/FiniteStateMachineAIBoss1.h"
#include "FiniteStateMachine/State/StateBossAI1.h"

void FiniteStateMachineAIBoss1::Initialize()
{

}

void FiniteStateMachineAIBoss1::Tick(float A_DeltaTime)
{
	if (CurrentState != nullptr)
	{
		CurrentState->Tick(A_DeltaTime);
	}
}

void FiniteStateMachineAIBoss1::Transition(StateBossAI1* A_NewState)
{
	if (CurrentState != nullptr)
	{
		CurrentState->Exit();
	}
	CurrentState = A_NewState;
	CurrentState->Enter();
}
