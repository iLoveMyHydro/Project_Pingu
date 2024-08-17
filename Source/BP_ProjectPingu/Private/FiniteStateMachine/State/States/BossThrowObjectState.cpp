// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/BossThrowObjectState.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/NormalFSM.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/NormalStateAI.h"
#include "BP_ProjectPingu/Private/Enemy/Character/BossEnemy.h"
#include "BP_ProjectPingu/Private/Enemy/Controller/BossAIController.h"

// Constructor for the State
BossThrowObjectState::BossThrowObjectState(FString A_Name, NormalFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

// Enters the State
void BossThrowObjectState::Enter()
{
	NormalStateAI::Enter();

	ThrowObject();
}

// Throws the Objects
void BossThrowObjectState::ThrowObject()
{
	Character = Machine->GetControllerBoss()->GetPawn<ABossEnemy>();
	if (Character == nullptr) return;

	Character->SetThrowAnimation();
	Character->ThrowOilBarrel();
}
