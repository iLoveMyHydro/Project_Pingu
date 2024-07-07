// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/AIControllerAI1.h"
#include "FiniteStateMachine/Machines/SimpleFSMAI1.h"
#include "Kismet/GameplayStatics.h"
#include "BP_ProjectPingu/Private/Enemy/Character/AIEnemy1.h"


void AAIControllerAI1::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(Fsm == nullptr)
	{
		Fsm = static_cast<FiniteStateMachineAI1*>(new SimpleFSMAI1(this));
	}
	if(Fsm != nullptr)
	{
		Fsm->Initialize();
	}
}

void AAIControllerAI1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Fsm != nullptr)
	{
		Fsm->Tick(DeltaTime);
	}
}
