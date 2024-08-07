// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */

class ABossAIController;
class NormalStateAI;
class ANormalAIController;

class NormalFSM
{
public:
	explicit inline NormalFSM(ANormalAIController* A_Controller) : FsmControllerNormal(A_Controller) {};
	explicit inline NormalFSM(ABossAIController* A_Controller) : FsmControllerBoss(A_Controller) {};
	virtual ~NormalFSM() {};

	virtual void Initialize(void);
	virtual void Tick(float A_DeltaTime);

	ANormalAIController* GetController(void) const { return FsmControllerNormal; }
	ABossAIController* GetControllerBoss(void) const { return FsmControllerBoss; }

	inline void SetBossController(ABossAIController* A_Controller) { FsmControllerBoss = A_Controller; }


	void Transition(NormalStateAI* A_NewState);

	NormalStateAI* GetCurrentState(void) const;

protected:
	NormalStateAI* CurrentState = nullptr;
	ANormalAIController* FsmControllerNormal = nullptr;
	ABossAIController* FsmControllerBoss = nullptr;
};
