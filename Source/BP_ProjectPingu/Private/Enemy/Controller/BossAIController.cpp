// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/BossAIController.h"
#include "FiniteStateMachine/Machines/NormalSimpleFSM.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PinguCharacter.h"

ABossAIController::ABossAIController()
{
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(Fsm == nullptr)
	{
		Fsm = static_cast<NormalFSM*>(new NormalSimpleFSM(this));
	}
	if(Fsm != nullptr)
	{
		Fsm->Initialize();
	}
}

void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Fsm != nullptr)
	{
		Fsm->Tick(DeltaTime);
	}
}
