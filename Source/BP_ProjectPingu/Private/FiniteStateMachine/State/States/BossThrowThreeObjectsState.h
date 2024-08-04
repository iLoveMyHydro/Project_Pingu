// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/BossStateAI.h"

/**
 * 
 */
class BossThrowThreeObjectsState : public BossStateAI
{
public:
	BossThrowThreeObjectsState(FString A_Name, BossFSM* A_Machine);
	virtual ~BossThrowThreeObjectsState() override {};

	virtual void Enter() override;

private:
	void ThrowThreeObjects(void);

	class ABossEnemy* Character = nullptr;
};
