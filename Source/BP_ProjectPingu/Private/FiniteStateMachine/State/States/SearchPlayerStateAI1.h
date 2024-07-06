// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/StateAI1.h"


/**
 * 
 */
class SearchPlayerStateAI1 : public StateAI1
{
public:
	SearchPlayerStateAI1(FString a_name, FiniteStateMachineAI1* a_machine);
	inline ~SearchPlayerStateAI1();

	virtual void Enter(void) override;
	virtual void Tick(float a_deltaTime) override;
};
