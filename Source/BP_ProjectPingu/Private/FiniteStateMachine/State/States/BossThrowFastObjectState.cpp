// Fill out your copyright notice in the Description page of Project Settings.


#include "BossThrowFastObjectState.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"
#include "FiniteStateMachine/State/NormalStateAI.h"
#include "Enemy/Character/BossEnemy.h"
#include "Enemy/Controller/BossAIController.h"

BossThrowFastObjectsState::BossThrowFastObjectsState(FString A_Name, NormalFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void BossThrowFastObjectsState::Enter()
{
	NormalStateAI::Enter();

	ThrowFastObject();
}

void BossThrowFastObjectsState::ThrowFastObject()
{
	Character = Machine->GetControllerBoss()->GetPawn<ABossEnemy>();
	if (Character == nullptr) return;

	Character->ThrowOilBarrelFast();
}
