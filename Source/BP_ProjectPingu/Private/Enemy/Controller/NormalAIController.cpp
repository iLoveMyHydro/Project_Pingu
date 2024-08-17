// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/NormalAIController.h"
#include "FiniteStateMachine/Machines/NormalSimpleFSM.h"
#include "Kismet/GameplayStatics.h"
#include "BP_ProjectPingu/Private/Player/PinguCharacter.h"

// Sets default values
ANormalAIController::ANormalAIController()
{
}

// Called when the game starts or when spawned
void ANormalAIController::BeginPlay()
{
	Super::BeginPlay();

	// Setting the FSM
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (Fsm == nullptr)
	{
		Fsm = static_cast<NormalFSM*>(new NormalSimpleFSM(this));
	}
	if (Fsm != nullptr)
	{
		Fsm->Initialize();
	}
}

// Called every frame
void ANormalAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tick for the FSM
	if (Fsm != nullptr)
	{
		Fsm->Tick(DeltaTime);
	}
}
