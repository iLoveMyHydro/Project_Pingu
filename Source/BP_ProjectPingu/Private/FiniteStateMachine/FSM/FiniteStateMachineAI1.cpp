// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "FiniteStateMachine/State/StateAI1.h"

void FiniteStateMachineAI1::Initialize()
{
	
}

void FiniteStateMachineAI1::Tick(float a_deltaTime)
{
	if(currentState != nullptr)
	{
		currentState->Tick(a_deltaTime);
	}
}

void FiniteStateMachineAI1::Transition(StateAI1* a_newState)
{
	if(currentState != nullptr)
	{
		currentState->Exit();
	}
	currentState = a_newState;
	currentState->Enter();
}
