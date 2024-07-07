// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/StateBossAI1.h"

/**
 * 
 */
class SearchPlayerStateBossAI1 : public  StateBossAI1
{
public:
	SearchPlayerStateBossAI1(FString A_Name, FiniteStateMachineAIBoss1* A_Machine);
	virtual ~SearchPlayerStateBossAI1() override {};

	virtual void Tick(float A_DeltaTime);

	static void SearchPlayer(AActor* A_Player);
};
