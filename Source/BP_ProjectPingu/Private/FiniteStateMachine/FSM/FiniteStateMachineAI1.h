// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */

class ANormalAIController;
class StateAI1;

class FiniteStateMachineAI1
{
public:
	explicit inline FiniteStateMachineAI1(ANormalAIController* A_Controller) : FsmController(A_Controller) {};
	virtual ~FiniteStateMachineAI1() {};

	virtual void Initialize(void);
	virtual void Tick(float A_DeltaTime);

	ANormalAIController* GetController(void) const { return FsmController; }

	void Transition(StateAI1* A_NewState);

	StateAI1* GetCurrentState(void) const;

protected:
	StateAI1* CurrentState = nullptr;
	ANormalAIController* FsmController = nullptr;
};
