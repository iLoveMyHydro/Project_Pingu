// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/BossThrowObjectState.h"
#include "FiniteStateMachine/FSM/BossFSM.h"
#include "FiniteStateMachine/State/BossStateAI.h"
#include "Enemy/Character/BossEnemy.h"
#include "Enemy/Controller/BossAIController.h"

BossThrowObjectState::BossThrowObjectState(FString A_Name, BossFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void BossThrowObjectState::Enter()
{
	BossStateAI::Enter();
}

void BossThrowObjectState::ThrowObject()
{
	Character = Machine->GetController()->GetPawn<ABossEnemy>();
	if (Character == nullptr) return;

	Character->ThrowOilBarrel();

	//TODO: Implement Animation for Enemy
	//Character->SetNootAnimation();
}
