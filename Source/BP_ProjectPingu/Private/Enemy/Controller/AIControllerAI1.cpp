// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/AIControllerAI1.h"
#include "FiniteStateMachine/Machines/SimpleFSMAI1.h"
#include "Kismet/GameplayStatics.h"
#include "BP_ProjectPingu/Private/Enemy/Character/AIEnemy1.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIControllerAI1::AAIControllerAI1()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(*PERCEPTION_NAME);
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	SightConfig->LoseSightRadius = 1000;
	SightConfig->SightRadius = 2500;
	SightConfig->PeripheralVisionAngleDegrees = 45.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerAI1::AttackPlayer);
}

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

void AAIControllerAI1::AttackPlayer(AActor* OtherActor, FAIStimulus Stimulus)
{
	//UE_LOG(LogTemp, Warning, TEXT("Player"));
}

void AAIControllerAI1::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (PerceptionComponent)
	{
		PerceptionComponent->OnTargetPerceptionUpdated.RemoveDynamic(this, &AAIControllerAI1::AttackPlayer);
	}
}
