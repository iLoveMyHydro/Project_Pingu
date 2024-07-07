// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/StateBossAI1.h"

/**
 * 
 */
class ThrowManyObjectsStateBossAI1 : public StateBossAI1
{
public:
	ThrowManyObjectsStateBossAI1(FString A_Name, FiniteStateMachineAIBoss1* A_Machine);
	virtual ~ThrowManyObjectsStateBossAI1() override {};

	virtual void Enter() override;
	virtual void Tick(float DeltaTime) override;

private:
	void ThrowManyObjects(void);
};
