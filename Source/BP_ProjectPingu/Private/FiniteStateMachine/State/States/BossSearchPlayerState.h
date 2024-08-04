// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/State/BossStateAI.h"

/**
 * 
 */
class BossSearchPlayerState : public BossStateAI
{
public:
	BossSearchPlayerState(FString A_Name, BossFSM* A_Machine);
	virtual ~BossSearchPlayerState() override {};

	virtual void Tick(float A_DeltaTime) override;

	void SearchPlayer();
};
