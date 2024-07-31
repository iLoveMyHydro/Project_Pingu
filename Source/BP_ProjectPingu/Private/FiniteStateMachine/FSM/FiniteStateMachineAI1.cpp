// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "FiniteStateMachine/State/StateAI1.h"

void FiniteStateMachineAI1::Initialize()
{
	
}

void FiniteStateMachineAI1::Tick(float A_DeltaTime)
{
	if(CurrentState != nullptr)
	{
		CurrentState->Tick(A_DeltaTime);
	}
}

void FiniteStateMachineAI1::Transition(StateAI1* A_NewState)
{
	if(CurrentState != nullptr)
	{
		CurrentState->Exit();
	}
	CurrentState = A_NewState;
	CurrentState->Enter();
}

StateAI1* FiniteStateMachineAI1::GetCurrentState() const
{
	return CurrentState;
}
