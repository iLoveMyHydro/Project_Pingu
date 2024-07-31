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

	//Counter = 0;
}

void SearchPlayerStateAI1::Tick(float A_DeltaTime)
{
	StateAI1::Tick(A_DeltaTime);


	if(Counter >= 5)
	{
		SearchPlayer();

		Counter = 0;
	}
	Counter += A_DeltaTime;
}

void SearchPlayerStateAI1::SearchPlayer()
{
	Character = Machine->GetController()->GetPawn<AAIEnemy1>();
	auto Rotation = Character->GetActorRotation();
	Character->SetActorRotation(Rotation + Rotator);
}
