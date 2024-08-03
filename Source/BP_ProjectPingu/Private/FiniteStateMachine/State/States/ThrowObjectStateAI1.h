// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "FiniteStateMachine/State/StateAI1.h"

class ANormalEnemy;

/**
 * 
 */
class ThrowObjectStateAI1 : public StateAI1
{
public:
	ThrowObjectStateAI1(FString A_Name, FiniteStateMachineAI1* A_Machine);
	virtual ~ThrowObjectStateAI1() override {};

	virtual void Enter(void) override;

private:
	void ThrowObject(void);

	class ANormalEnemy* Character = nullptr;
};
