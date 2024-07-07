// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAIBoss1.h"

/**
 * 
 */
class StateBossAI1
{
public:
	inline StateBossAI1() {};
	inline StateBossAI1(const FString& A_Name, FiniteStateMachineAIBoss1* A_Machine) : Name(A_Name), Machine(A_Machine) {};
	inline virtual ~StateBossAI1() {};

	virtual void Enter(void);
	virtual void Tick(float DeltaTime);
	virtual void Exit(void);

	inline const FString GetName() { return Name; }

protected:
	FString Name = TEXT("");
	FiniteStateMachineAIBoss1* Machine = nullptr;

};
