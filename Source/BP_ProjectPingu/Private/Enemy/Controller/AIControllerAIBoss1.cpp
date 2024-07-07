// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/AIControllerAIBoss1.h"
#include "Kismet/GameplayStatics.h"
#include "BP_ProjectPingu/Private/Enemy/Character/AIBossEnemy1.h"
#include "FiniteStateMachine/Machines/SimpleFSMBossAI1.h"

void AAIControllerAIBoss1::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(Fsm == nullptr)
	{
		Fsm = static_cast<FiniteStateMachineAIBoss1*>(new SimpleFSMBossAI1(this));
	}
	if(Fsm != nullptr)
	{
		Fsm->Initialize();
	}
}

void AAIControllerAIBoss1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Fsm != nullptr)
	{
		Fsm->Tick(DeltaTime);
	}
}


