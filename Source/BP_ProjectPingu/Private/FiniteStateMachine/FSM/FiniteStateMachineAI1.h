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
	inline FiniteStateMachineAI1(AAIControllerAI1* a_controller) : fsmController(a_controller) {}
	inline ~FiniteStateMachineAI1() {};

	virtual void Initialize(void);
	virtual void Tick(float a_deltaTime);

	AAIControllerAI1* GetController(void) { return fsmController; }

	void Transition(StateAI1* a_newState);

protected:
	StateAI1* currentState = nullptr;
	AAIControllerAI1* fsmController = nullptr;
};
