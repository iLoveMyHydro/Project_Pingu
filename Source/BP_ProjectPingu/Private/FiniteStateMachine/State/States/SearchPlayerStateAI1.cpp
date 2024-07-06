// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/SearchPlayerStateAI1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/Machines/SimpleFSMAI1.h"


SearchPlayerStateAI1::SearchPlayerStateAI1(FString a_name, FiniteStateMachineAI1* a_machine) : name(a_name), machine(a_machine) {}

void SearchPlayerStateAI1::Enter()
{
	StateAI1::Enter();
}

void SearchPlayerStateAI1::Tick(float a_deltaTime)
{
	StateAI1::Tick(a_deltaTime);
}
