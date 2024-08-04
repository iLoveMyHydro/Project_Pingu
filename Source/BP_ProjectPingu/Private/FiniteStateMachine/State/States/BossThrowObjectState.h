// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/BossStateAI.h"

class ABossEnemy;

/**
 * 
 */
class BossThrowObjectState : public BossStateAI
{
public:
	BossThrowObjectState(FString A_Name, BossFSM* A_Machine);
	virtual ~BossThrowObjectState() override {};

	virtual void Enter() override;

private:
	void ThrowObejct(void);

	class ABossEnemy* Character = nullptr;
};
