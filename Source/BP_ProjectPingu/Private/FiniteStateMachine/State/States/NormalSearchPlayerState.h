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
	NormalSearchPlayerState(FString A_Name, NormalFSM* A_Machine);
	virtual ~NormalSearchPlayerState() override {};

	virtual void Tick(float A_DeltaTime) override;

	void SearchPlayer();
};
