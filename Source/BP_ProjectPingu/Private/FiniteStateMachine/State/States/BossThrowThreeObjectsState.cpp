// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/BossThrowThreeObjectsState.h"
#include "FiniteStateMachine/FSM/BossFSM.h"
#include "FiniteStateMachine/State/BossStateAI.h"
#include "Enemy/Character/BossEnemy.h"
#include "Enemy/Controller/BossAIController.h"

BossThrowThreeObjectsState::BossThrowThreeObjectsState(FString A_Name, BossFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void BossThrowThreeObjectsState::Enter()
{
	BossStateAI::Enter();
}

void BossThrowThreeObjectsState::ThrowThreeObjects()
{
	Character = Machine->GetController()->GetPawn<ABossEnemy>();
	if (Character == nullptr) return;

	Character->ThrowThreeOilBarel();

	//TODO: Implement Animation for Enemy
	//Character->SetNootAnimation();
}
