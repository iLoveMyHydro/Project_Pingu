// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/NormalThrowObjectState.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/NormalFSM.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/NormalStateAI.h"
#include "BP_ProjectPingu/Private/Enemy/Character/NormalEnemy.h"
#include "BP_ProjectPingu/Private/Enemy/Controller/NormalAIController.h"


NormalThrowObjectState::NormalThrowObjectState(FString A_Name, NormalFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void NormalThrowObjectState::Enter()
{
	NormalStateAI::Enter();

	ThrowObject();
}

void NormalThrowObjectState::ThrowObject()
{
	Character = Machine->GetController()->GetPawn<ANormalEnemy>();
	if (Character == nullptr) return;

	Character->ThrowOilBarrel();

	//TODO: Implement Animation for Enemy
	//Character->SetNootAnimation();
}
