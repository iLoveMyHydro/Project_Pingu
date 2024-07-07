// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/ThrowObjectStateBossAI1.h"

ThrowObjectStateBossAI1::ThrowObjectStateBossAI1(FString A_Name, FiniteStateMachineAIBoss1* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void ThrowObjectStateBossAI1::Tick(float DeltaTime)
{
	StateBossAI1::Tick(DeltaTime);
}

void ThrowObjectStateBossAI1::ThrowObject()
{
	//TODO:
}

