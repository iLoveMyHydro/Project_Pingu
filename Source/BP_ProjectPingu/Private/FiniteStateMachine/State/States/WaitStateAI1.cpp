// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/WaitStateAI1.h"

WaitStateAI1::WaitStateAI1(FString a_name, FiniteStateMachineAI1* a_machine) : name(a_name), machine(a_machine) {}

void WaitStateAI1::Tick(float a_deltaTime)
{
	if(WaitTime == 0)
	{
		WaitTime = 2;
	}
	else
	{
		WaitTime--;
	}
}
