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
	inline SimpleFSMAI1(AAIControllerAI1* a_controller) : FiniteStateMachineAI1(a_controller) {};
	inline ~SimpleFSMAI1() {};

	void Initialize() override;

	StateAI1* GetSearchPlayerState(void) { return SearchPlayerState; }
	StateAI1* GetThrowObjectState(void) { return ThrowObjectState; }
	StateAI1* GetWaitState(void) { return WaitState; }

private:
	const FString SEARCH_PLAYER_STATE = TEXT("Search Player State");
	const FString THROW_OBJECT_STATE = TEXT("Throw Object State");
	const FString WAIT_STATE = TEXT("Wait State");

	//States
	StateAI1* SearchPlayerState = nullptr;
	StateAI1* ThrowObjectState = nullptr;
	StateAI1* WaitState = nullptr;
};
