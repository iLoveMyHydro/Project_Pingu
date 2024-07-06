// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "FiniteStateMachine/State/StateAI1.h"

/**
 * 
 */
class ThrowObjectStateAI1 : public StateAI1
{
public:
	ThrowObjectStateAI1(FString a_name, FiniteStateMachineAI1* a_machine);
	inline ~ThrowObjectStateAI1() {};

	virtual void Enter(void) override;
	virtual void Tick(float a_deltaTime) override;

private:
	void ThrowObject(void);
};
