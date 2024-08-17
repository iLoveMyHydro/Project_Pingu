// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"
#include "FiniteStateMachine/State/NormalStateAI.h"

class ANormalEnemy;

/**
 * 
 */
class NormalThrowObjectState : public NormalStateAI
{
public:
	// Constructor for the State
	NormalThrowObjectState(FString A_Name, NormalFSM* A_Machine);

	// Deconstructor for the State
	virtual ~NormalThrowObjectState() override {};

	// Enters the State
	virtual void Enter(void) override;

private:
	// State
	void ThrowObject(void);

	// Normal Enemy
	class ANormalEnemy* Character = nullptr;
};
