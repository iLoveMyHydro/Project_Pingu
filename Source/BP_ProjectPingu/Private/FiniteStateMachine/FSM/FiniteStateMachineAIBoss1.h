// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class StateBossAI1;
class AAIControllerAIBoss1;

/**
 * 
 */
class FiniteStateMachineAIBoss1
{
public:
	explicit inline FiniteStateMachineAIBoss1(AAIControllerAIBoss1* A_Controller) : FsmController(A_Controller) {};
	virtual ~FiniteStateMachineAIBoss1() {};

	virtual void Initialize(void);
	virtual void Tick(float A_DeltaTime);

	AAIControllerAIBoss1* GetController(void) const { return FsmController; }

	void Transition(StateBossAI1* A_NewState);

protected:
	StateBossAI1* CurrentState = nullptr;
	AAIControllerAIBoss1* FsmController = nullptr;
};
