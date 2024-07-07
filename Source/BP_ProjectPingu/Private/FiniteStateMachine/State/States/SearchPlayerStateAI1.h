// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "FiniteStateMachine/State/StateAI1.h"
#include "FiniteStateMachine/State/StateBossAI1.h"

class AIControllerAI1;

/**
 * 
 */
class SearchPlayerStateAI1 : public StateAI1
{
public:
	SearchPlayerStateAI1(FString A_Name, FiniteStateMachineAI1* A_Machine);
	virtual ~SearchPlayerStateAI1() override {};

	virtual void Tick(float A_DeltaTime) override;

	static void SearchPlayer(AActor* A_Player);
};
