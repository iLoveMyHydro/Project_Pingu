// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/StateAI1.h"

/**
 * 
 */
class WaitStateAI1 : public StateAI1
{

public:
	WaitStateAI1(FString a_name, FiniteStateMachineAI1* a_machine);

	void Tick(float a_deltaTime) override;

private:

	int WaitTime = 2;
};
