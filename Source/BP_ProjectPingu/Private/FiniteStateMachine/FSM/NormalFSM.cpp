// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/FSM/NormalFSM.h"
#include "FiniteStateMachine/State/NormalStateAI.h"

void NormalFSM::Initialize()
{
}

void NormalFSM::Tick(float A_DeltaTime)
{
	if(CurrentState != nullptr)
	{
		CurrentState->Tick(A_DeltaTime);
	}
}

void NormalFSM::Transition(NormalStateAI* A_NewState)
{
	if(CurrentState != nullptr)
	{
		CurrentState->Exit();
	}
	CurrentState = A_NewState;
	CurrentState->Enter();
}

NormalStateAI* NormalFSM::GetCurrentState() const
{
	return CurrentState;
}
