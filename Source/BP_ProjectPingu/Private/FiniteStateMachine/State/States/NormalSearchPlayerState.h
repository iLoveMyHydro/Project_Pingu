// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/NormalStateAI.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"

/**
 * 
 */
class NormalSearchPlayerState : public NormalStateAI
{
public:
	// Constructor for the State
	NormalSearchPlayerState(FString A_Name, NormalFSM* A_Machine);

	// Deconstructor for the State
	virtual ~NormalSearchPlayerState() override {};

	// Called every frame
	virtual void Tick(float A_DeltaTime) override;

	// Search the Player
	void SearchPlayer();
};
