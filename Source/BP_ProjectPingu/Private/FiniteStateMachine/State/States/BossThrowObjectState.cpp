// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/BossThrowObjectState.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/NormalFSM.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/NormalStateAI.h"
#include "BP_ProjectPingu/Private/Enemy/Character/BossEnemy.h"
#include "BP_ProjectPingu/Private/Enemy/Controller/BossAIController.h"

BossThrowObjectState::BossThrowObjectState(FString A_Name, NormalFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void BossThrowObjectState::Enter()
{
	NormalStateAI::Enter();

	ThrowObject();
}

void BossThrowObjectState::ThrowObject()
{
	Character = Machine->GetControllerBoss()->GetPawn<ABossEnemy>();
	if (Character == nullptr) return;

	Character->ThrowOilBarrel();

	//TODO: Implement Animation for Enemy
	//Character->SetNootAnimation();
}
