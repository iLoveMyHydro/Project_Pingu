// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/AIControllerAI1.h"
#include "FiniteStateMachine/Machines/SimpleFSMAI1.h"
#include "Kismet/GameplayStatics.h"
#include "BP_ProjectPingu/Private/Enemy/Character/AIEnemy1.h"

void AAIControllerAI1::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(fsm == nullptr)
	{
		fsm = static_cast<FiniteStateMachineAI1*>(new SimpleFSMAI1(this));
	}
	if(fsm != nullptr)
	{
		fsm->Initialize();
	}
}

void AAIControllerAI1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(fsm != nullptr)
	{
		fsm->Tick(DeltaTime);
	}
}
