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
	// Constructor for the Normal Enemy
	explicit inline NormalFSM(ANormalAIController* A_Controller) : FsmControllerNormal(A_Controller) {};

	// Constructor for the Boss Enemy
	explicit inline NormalFSM(ABossAIController* A_Controller) : FsmControllerBoss(A_Controller) {};

	// Deconstructor
	virtual ~NormalFSM() {};

	// Initialize for the FSM
	virtual void Initialize(void);

	// Tick for the FSM
	virtual void Tick(float A_DeltaTime);

	// Gets the Controller for the Normal Enemy
	ANormalAIController* GetController(void) const { return FsmControllerNormal; }

	// Gets the Controller for the Boss Enemy
	ABossAIController* GetControllerBoss(void) const { return FsmControllerBoss; }

	// Transition for the FSM
	void Transition(NormalStateAI* A_NewState);

	// Gets the current State
	NormalStateAI* GetCurrentState(void) const;

protected:
	// Current State
	NormalStateAI* CurrentState = nullptr;

	// FSM Controller for the Normal Enemy
	ANormalAIController* FsmControllerNormal = nullptr;

	// FSM Controller for Boss Enemy
	ABossAIController* FsmControllerBoss = nullptr;
};
