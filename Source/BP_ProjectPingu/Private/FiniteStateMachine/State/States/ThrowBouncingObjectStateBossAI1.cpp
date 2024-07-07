// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/ThrowBouncingObjectStateBossAI1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/FiniteStateMachineAIBoss1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/StateBossAI1.h"

ThrowBouncingObjectStateBossAI1::ThrowBouncingObjectStateBossAI1(FString A_Name, FiniteStateMachineAIBoss1* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void ThrowBouncingObjectStateBossAI1::Enter()
{
	StateBossAI1::Enter();
}

void ThrowBouncingObjectStateBossAI1::Tick(float DeltaTime)
{
	StateBossAI1::Tick(DeltaTime);
}

void ThrowBouncingObjectStateBossAI1::ThrowBouncingObject()
{
	//TODO:
}
