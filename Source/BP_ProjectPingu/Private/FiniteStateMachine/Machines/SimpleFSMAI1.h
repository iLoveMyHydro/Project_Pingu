// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"

/**
 * 
 */
class SimpleFSMAI1 : public FiniteStateMachineAI1
{
public:
	inline SimpleFSMAI1(AAIControllerAI1* A_Controller) : FiniteStateMachineAI1(A_Controller) {};
	inline ~SimpleFSMAI1() {};

	virtual void Initialize() override;

	StateAI1* GetSearchPlayerState(void) const { return SearchPlayerState; }
	StateAI1* GetThrowObjectState(void) const { return ThrowObjectState; }
	StateAI1* GetWaitState(void) const { return WaitState; }

private:
	const FString SEARCH_PLAYER_STATE = TEXT("Search Player State");
	const FString THROW_OBJECT_STATE = TEXT("Throw Object State");
	const FString WAIT_STATE = TEXT("Wait State");

	//States
	StateAI1* SearchPlayerState = nullptr;
	StateAI1* ThrowObjectState = nullptr;
	StateAI1* WaitState = nullptr;
};
