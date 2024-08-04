// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/State/States/BossSearchPlayerState.h"
#include "FiniteStateMachine/FSM/BossFSM.h"
#include "FiniteStateMachine/State/BossStateAI.h"

BossSearchPlayerState::BossSearchPlayerState(FString A_Name, BossFSM* A_Machine)
{
	Name = A_Name;
	Machine = A_Machine;
}

void BossSearchPlayerState::Tick(float A_DeltaTime)
{
	BossStateAI::Tick(A_DeltaTime);
}

void BossSearchPlayerState::SearchPlayer()
{
}
