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
	NormalThrowObjectState(FString A_Name, NormalFSM* A_Machine);
	virtual ~NormalThrowObjectState() override {};

	virtual void Enter(void) override;

private:
	void ThrowObject(void);

	class ANormalEnemy* Character = nullptr;
};
