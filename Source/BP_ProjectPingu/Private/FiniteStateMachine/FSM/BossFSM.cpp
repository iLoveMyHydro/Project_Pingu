// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/FSM/BossFSM.h"
#include "FiniteStateMachine/State/BossStateAI.h"

void BossFSM::Initialize()
{
}

void BossFSM::Tick(float A_DeltaTime)
{
	if(CurrentState != nullptr)
	{
		CurrentState->Tick(A_DeltaTime);
	}
}

void BossFSM::Transition(BossStateAI* A_NewState)
{
	if (CurrentState != nullptr)
	{
		CurrentState->Exit();
	}
	CurrentState = A_NewState;
	CurrentState->Enter();
}

BossStateAI* BossFSM::GetCurrentState() const
{
	return CurrentState;
}
