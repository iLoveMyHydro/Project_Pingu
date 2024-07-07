// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/WaitStateBossAI1.h"

WaitStateBossAI1::WaitStateBossAI1(FString A_Name, FiniteStateMachineAIBoss1* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void WaitStateBossAI1::Tick(float DeltaTime)
{
	StateBossAI1::Tick(DeltaTime);

	if (WaitTime == 0)
	{
		WaitTime = 1;
	}
	else
	{
		WaitTime--;
	}
}
