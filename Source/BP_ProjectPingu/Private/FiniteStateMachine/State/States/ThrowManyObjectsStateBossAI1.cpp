// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/ThrowManyObjectsStateBossAI1.h"

ThrowManyObjectsStateBossAI1::ThrowManyObjectsStateBossAI1(FString A_Name, FiniteStateMachineAIBoss1* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void ThrowManyObjectsStateBossAI1::Enter()
{
	StateBossAI1::Enter();
}

void ThrowManyObjectsStateBossAI1::Tick(float DeltaTime)
{
	StateBossAI1::Tick(DeltaTime);
}

void ThrowManyObjectsStateBossAI1::ThrowManyObjects()
{
	//TODO:
}
