// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"
#include "FiniteStateMachine/State/States/NormalThrowObjectState.h"

/**
 * 
 */
class NormalSimpleFSM : public NormalFSM
{
public:
	inline NormalSimpleFSM(ANormalAIController* A_Controller) : NormalFSM(A_Controller) {};
	inline ~NormalSimpleFSM() {};

	virtual void Initialize() override;

	NormalStateAI* GetSearchPlayerState(void) const { return SearchPlayerState; }
	NormalStateAI* GetThrowObjectState(void) const { return ThrowObjectState; }

private:
	const FString SEARCH_PLAYER_STATE = TEXT("Search Player State");
	const FString THROW_OBJECT_STATE = TEXT("Throw Object State");

	//States
	NormalStateAI* SearchPlayerState = nullptr;
	NormalStateAI* ThrowObjectState = nullptr;
};
