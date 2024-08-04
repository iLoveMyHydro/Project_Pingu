// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */

class NormalStateAI;
class ANormalAIController;

class NormalFSM
{
public:
	explicit inline NormalFSM(ANormalAIController* A_Controller) : FsmController(A_Controller) {};
	virtual ~NormalFSM() {};

	virtual void Initialize(void);
	virtual void Tick(float A_DeltaTime);

	ANormalAIController* GetController(void) const { return FsmController; }

	void Transition(NormalStateAI* A_NewState);

	NormalStateAI* GetCurrentState(void) const;

protected:
	NormalStateAI* CurrentState = nullptr;
	ANormalAIController* FsmController = nullptr;
};
