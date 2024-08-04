// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/State/NormalStateAI.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"

class AIControllerAI1;
class NormalEnemy;

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

	class NormalEnemy* Character = nullptr;

	FRotator Rotator = FRotator(0.0f, 180.0f, 0.0f);

	float Counter = 0;
};
