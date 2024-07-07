// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAIBoss1.h"
#include "FiniteStateMachine/State/StateBossAI1.h"

/**
 * 
 */
class ThrowObjectStateBossAI1 : public StateBossAI1
{
public:
	ThrowObjectStateBossAI1(FString A_Name, FiniteStateMachineAIBoss1* A_Machine);
	virtual ~ThrowObjectStateBossAI1() override {};

	virtual void Tick(float DeltaTime) override;

private:
	void ThrowObject(void);
};
