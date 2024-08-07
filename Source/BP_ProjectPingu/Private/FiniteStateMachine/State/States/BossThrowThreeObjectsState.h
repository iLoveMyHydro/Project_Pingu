// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/NormalStateAI.h"

/**
 * 
 */
class BossThrowThreeObjectsState : public NormalStateAI
{
public:
	BossThrowThreeObjectsState(FString A_Name, NormalFSM* A_Machine);
	virtual ~BossThrowThreeObjectsState() override {};

	virtual void Enter() override;

private:
	void ThrowThreeObjects(void);

	class ABossEnemy* Character = nullptr;
};
