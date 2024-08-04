// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class BossStateAI;
class ABossAIController;
/**
 * 
 */
class BossFSM
{
public:
	explicit BossFSM(ABossAIController* A_Controller) : FsmController(A_Controller) {};
	virtual ~BossFSM() {};

	virtual void Initialize(void);
	virtual void Tick(float A_DeltaTime);

	ABossAIController* GetController(void) const { return FsmController; }

	void Transition(BossStateAI* A_NewState);

	BossStateAI* GetCurrentState(void) const;

protected:
	BossStateAI* CurrentState = nullptr;
	ABossAIController* FsmController = nullptr;
};
