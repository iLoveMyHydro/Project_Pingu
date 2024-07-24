
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/StateAI1.h"


class FiniteStateMachineAI1;
/**
 * 
 */
class WaitStateAI1 : public StateAI1
{

public:
	WaitStateAI1(FString A_Name, FiniteStateMachineAI1* A_Machine);
	virtual ~WaitStateAI1() override {};
	void Tick(float DeltaTime) override;

private:
	int WaitTime = 2;
};