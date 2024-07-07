// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FiniteStateMachineAI1;

/**
 * 
 */
class StateAI1
{
public:
	inline StateAI1() {};
	inline StateAI1(const FString& A_Name, FiniteStateMachineAI1* A_Machine) : Name(A_Name), Machine(A_Machine) {}
	inline virtual ~StateAI1() {};

	virtual void Enter(void);
	virtual void Tick(float a_deltaTime);
	virtual void Exit(void);

	inline const FString GetName() { return Name; }

protected:
	FString Name = TEXT("");
	FiniteStateMachineAI1* Machine = nullptr;
};
