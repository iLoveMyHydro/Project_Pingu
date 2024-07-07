// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/SearchPlayerStateAI1.h"

SearchPlayerStateAI1::SearchPlayerStateAI1(FString A_Name, FiniteStateMachineAI1* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void SearchPlayerStateAI1::Tick(float A_DeltaTime)
{
	StateAI1::Tick(A_DeltaTime);
}

void SearchPlayerStateAI1::SearchPlayer(AActor* A_Player)
{
	//TODO:
}
