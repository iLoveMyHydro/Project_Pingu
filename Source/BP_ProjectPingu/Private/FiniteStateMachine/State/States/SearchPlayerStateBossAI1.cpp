// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/SearchPlayerStateBossAI1.h"

SearchPlayerStateBossAI1::SearchPlayerStateBossAI1(FString A_Name, FiniteStateMachineAIBoss1* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void SearchPlayerStateBossAI1::Tick(float A_DeltaTime)
{
	StateBossAI1::Tick(A_DeltaTime);
}

void SearchPlayerStateBossAI1::SearchPlayer(AActor* A_Player)
{
	//TODO:
}
