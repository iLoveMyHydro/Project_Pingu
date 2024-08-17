// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/NormalSearchPlayerState.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/NormalFSM.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/NormalStateAI.h"

// Constructor for the State
NormalSearchPlayerState::NormalSearchPlayerState(FString A_Name, NormalFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

// Called every frame
void NormalSearchPlayerState::Tick(float A_DeltaTime)
{
	NormalStateAI::Tick(A_DeltaTime);
}

// Search the player
void NormalSearchPlayerState::SearchPlayer()
{
}
