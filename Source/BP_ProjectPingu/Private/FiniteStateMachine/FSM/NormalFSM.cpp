// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/FSM/NormalFSM.h"
#include "FiniteStateMachine/State/NormalStateAI.h"

// Initialize the FSM
void NormalFSM::Initialize()
{
}

// Called every frame
void NormalFSM::Tick(float A_DeltaTime)
{
	if(CurrentState != nullptr)
	{
		CurrentState->Tick(A_DeltaTime);
	}
}

// Transition between the States
void NormalFSM::Transition(NormalStateAI* A_NewState)
{
	if(CurrentState != nullptr)
	{
		CurrentState->Exit();
	}
	CurrentState = A_NewState;
	CurrentState->Enter();
}

// Returns the Current State
NormalStateAI* NormalFSM::GetCurrentState() const
{
	return CurrentState;
}
