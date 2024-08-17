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
	// Constructor 
	inline NormalStateAI() {};

	// Constructor 
	inline NormalStateAI(const FString& A_Name, NormalFSM* A_Machine) : Name(A_Name), Machine(A_Machine) {}

	// Deconstructor
	inline virtual ~NormalStateAI() {};

	// Enters the State
	virtual void Enter(void);

	// called every frame 
	virtual void Tick(float A_DeltaTime);

	// Exits the State
	virtual void Exit(void);

	// Gets the Name of the State
	inline const FString GetName() { return Name; }

protected:
	FString Name = TEXT("");
	NormalFSM* Machine = nullptr;
};
