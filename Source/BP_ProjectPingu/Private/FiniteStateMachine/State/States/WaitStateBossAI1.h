// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/StateBossAI1.h"

/**
 * 
 */
class WaitStateBossAI1 : public  StateBossAI1
{
public:
	WaitStateBossAI1(FString A_Name, FiniteStateMachineAIBoss1* A_Machine);
	virtual ~WaitStateBossAI1() override {};
	void Tick(float DeltaTime) override;

private:
	int WaitTime = 1;
};
