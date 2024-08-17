// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/NormalStateAI.h"

/**
 * 
 */
class BossThrowFastObjectsState : public NormalStateAI
{
public:
	// Constructor for the State
	BossThrowFastObjectsState(FString A_Name, NormalFSM* A_Machine);

	// Deconstructor for the State
	virtual ~BossThrowFastObjectsState() override {};

	// Enters the State
	virtual void Enter() override;

private:
	// Throws the Object
	void ThrowFastObject(void);

	class ABossEnemy* Character = nullptr;
};
