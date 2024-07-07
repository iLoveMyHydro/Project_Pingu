// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/ThrowObjectStateAI1.h"
#include "Enemy/Controller/AIControllerAI1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/StateAI1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/Machines/SimpleFSMAI1.h"

ThrowObjectStateAI1::ThrowObjectStateAI1(FString A_Name, FiniteStateMachineAI1* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void ThrowObjectStateAI1::Enter()
{
	StateAI1::Enter();
}

void ThrowObjectStateAI1::Tick(float a_deltaTime)
{
	StateAI1::Tick(a_deltaTime);
}

void ThrowObjectStateAI1::ThrowObject()
{
	//TODO:
}
