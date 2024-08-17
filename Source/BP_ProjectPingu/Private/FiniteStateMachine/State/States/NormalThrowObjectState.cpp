// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/NormalThrowObjectState.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/NormalFSM.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/NormalStateAI.h"
#include "BP_ProjectPingu/Private/Enemy/Character/NormalEnemy.h"
#include "BP_ProjectPingu/Private/Enemy/Controller/NormalAIController.h"


// Constructor for the State
NormalThrowObjectState::NormalThrowObjectState(FString A_Name, NormalFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

// Enters the State
void NormalThrowObjectState::Enter()
{
	NormalStateAI::Enter();

	ThrowObject();
}

// Throws the Object
void NormalThrowObjectState::ThrowObject()
{
	Character = Machine->GetController()->GetPawn<ANormalEnemy>();
	if (Character == nullptr) return;

	Character->SetThrowAnimation();
	Character->ThrowOilBarrel();
}
