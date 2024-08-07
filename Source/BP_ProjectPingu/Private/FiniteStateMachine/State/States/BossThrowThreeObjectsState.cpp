// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/BossThrowThreeObjectsState.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"
#include "FiniteStateMachine/State/NormalStateAI.h"
#include "Enemy/Character/BossEnemy.h"
#include "Enemy/Controller/BossAIController.h"

BossThrowThreeObjectsState::BossThrowThreeObjectsState(FString A_Name, NormalFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void BossThrowThreeObjectsState::Enter()
{
	NormalStateAI::Enter();

	ThrowThreeObjects();
}

void BossThrowThreeObjectsState::ThrowThreeObjects()
{
	Character = Machine->GetControllerBoss()->GetPawn<ABossEnemy>();
	if (Character == nullptr) return;

	Character->ThrowThreeOilBarel();

	//TODO: Implement Animation for Enemy
	//Character->SetNootAnimation();
}
