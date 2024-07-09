// Fill out your copyright notice in the Description page of Project Settings.

#include "FiniteStateMachine/State/States/WaitStateAI1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/StateAI1.h"

WaitStateAI1::WaitStateAI1(FString A_Name, FiniteStateMachineAI1* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void WaitStateAI1::Tick(float DeltaTime)
{
	StateAI1::Tick(DeltaTime);

	if(WaitTime == 0)
	{
		WaitTime = 2;
	}
	else
	{
		WaitTime--;
	}
}
