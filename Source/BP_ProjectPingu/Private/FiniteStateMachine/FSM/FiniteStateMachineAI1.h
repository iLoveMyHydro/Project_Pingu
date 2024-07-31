// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */

class StateAI1;
class AAIControllerAI1;

class FiniteStateMachineAI1
{
public:
	explicit inline FiniteStateMachineAI1(AAIControllerAI1* A_Controller) : FsmController(A_Controller) {};
	virtual ~FiniteStateMachineAI1() {};

	virtual void Initialize(void);
	virtual void Tick(float A_DeltaTime);

	AAIControllerAI1* GetController(void) const { return FsmController; }

	void Transition(StateAI1* A_NewState);

	StateAI1* GetCurrentState(void) const;

protected:
	StateAI1* CurrentState = nullptr;
	AAIControllerAI1* FsmController = nullptr;
};
