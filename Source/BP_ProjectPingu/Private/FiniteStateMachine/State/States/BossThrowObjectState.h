// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"
#include "FiniteStateMachine/State/NormalStateAI.h"

/**
 * 
 */
class BossThrowObjectState : public NormalStateAI
{
public:
	// Constructor for the State
	BossThrowObjectState(FString A_Name, NormalFSM* A_Machine);

	// Deconstructor for the State
	virtual ~BossThrowObjectState() override {};

	// Enters the State
	virtual void Enter() override;

private:
	// Throws the Object
	void ThrowObject(void); 

	class ABossEnemy* Character = nullptr;
};
