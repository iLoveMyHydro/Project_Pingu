// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Character/OilBarrel/OilBarrel.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "FiniteStateMachine/State/StateAI1.h"

/**
 * 
 */
class ThrowObjectStateAI1 : public StateAI1
{
public:
	ThrowObjectStateAI1(FString A_Name, FiniteStateMachineAI1* A_Machine);
	virtual ~ThrowObjectStateAI1() override {};

	virtual void Enter(void) override;
	virtual void Tick(float a_deltaTime) override;

private:
	void ThrowObject(void);


	UPROPERTY()
	TObjectPtr<AOilBarrel> OilBarrel = nullptr;
};
