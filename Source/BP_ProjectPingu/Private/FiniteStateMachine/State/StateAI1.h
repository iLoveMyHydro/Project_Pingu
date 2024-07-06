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
	inline StateAI1(const FString& A_Name, FiniteStateMachineAI1* A_Machine) : name(A_Name), machine(A_Machine) {}
	inline virtual ~StateAI1() {};

	virtual void Enter(void);
	virtual void Tick(float a_deltaTime);
	virtual void Exit(void);

	inline const FString GetName() { return name; }

private:
	const FString ENTERING_STATE = TEXT("Entering State %s");
	const FString EXIT_STATE = TEXT("Exiting State %s");

protected:
	FString name = TEXT("");
	FiniteStateMachineAI1* machine = nullptr;
};
