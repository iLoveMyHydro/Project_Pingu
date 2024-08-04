// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"


/**
 * 
 */
class NormalStateAI
{
public:
	inline NormalStateAI() {};
	inline NormalStateAI(const FString& A_Name, NormalFSM* A_Machine) : Name(A_Name), Machine(A_Machine) {}
	inline virtual ~NormalStateAI() {};

	virtual void Enter(void);
	virtual void Tick(float A_DeltaTime);
	virtual void Exit(void);

	inline const FString GetName() { return Name; }

protected:
	FString Name = TEXT("");
	NormalFSM* Machine = nullptr;
};
