// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/SearchPlayerStateAI1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/StateAI1.h"
#include "BP_ProjectPingu/Private/Enemy/Character/AIEnemy1.h"
#include "BP_ProjectPingu/Private/Enemy/Controller/AIControllerAI1.h"

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
	Machine = nullptr;
	Character = Machine->GetController()->GetPawn<AAIEnemy1>();
	Character->SetActorRotation(FRotator(0.0f, 0.0f, 180.0f));
}
