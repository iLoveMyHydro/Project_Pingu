// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/StateAI1.h"

class AIControllerAI1;
class NormalEnemy;

/**
 * 
 */
class SearchPlayerStateAI1 : public StateAI1
{
public:
	SearchPlayerStateAI1(FString A_Name, FiniteStateMachineAI1* A_Machine);
	virtual ~SearchPlayerStateAI1() override {};

	virtual void Tick(float A_DeltaTime) override;

	void SearchPlayer();

	class NormalEnemy* Character = nullptr;

	FRotator Rotator = FRotator(0.0f, 180.0f, 0.0f);

	float Counter = 0;

};
