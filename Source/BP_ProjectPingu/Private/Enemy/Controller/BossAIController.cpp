// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/BossAIController.h"
#include "FiniteStateMachine/Machines/NormalSimpleFSM.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PinguCharacter.h"

// Sets default values
ABossAIController::ABossAIController()
{
}

// Called when the game starts or when spawned
void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	// Sets  the FSM for the Boss Enemy
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

// Called every frame
void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tick for the FSM
	if(Fsm != nullptr)
	{
		Fsm->Tick(DeltaTime);
	}
}
