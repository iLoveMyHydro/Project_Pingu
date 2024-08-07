// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"

/**
 * 
 */
class NormalSimpleFSM : public NormalFSM
{
public:
	inline NormalSimpleFSM(ANormalAIController* A_Controller) : NormalFSM(A_Controller) {};
	inline NormalSimpleFSM(ABossAIController* A_Controller) : NormalFSM(A_Controller) {};
	inline ~NormalSimpleFSM() {};

	virtual void Initialize() override;

	NormalStateAI* GetSearchPlayerState(void) const { return SearchPlayerState; }
	NormalStateAI* GetThrowObjectState(void) const { return ThrowObjectState; }
	NormalStateAI* GetBossThrowObjectState(void) const { return BossThrowObjectState; }
	NormalStateAI* GetThrowThreeObjectsState(void) const { return ThrowThreeObjectsState; }


private:
	const FString SEARCH_PLAYER_STATE = FString(TEXT("Search Player State"));
	const FString THROW_OBJECT_STATE = FString(TEXT("Throw Object State"));
	const FString THROW_THREE_OBJECTS_STATE = FString(TEXT("Throw Three Objects State"));
	const FString BOSS_THROW_OBJECT_STATE = FString(TEXT("Boss Throw Object State"));

	//States
	NormalStateAI* SearchPlayerState = nullptr;
	NormalStateAI* ThrowObjectState = nullptr;
	NormalStateAI* ThrowThreeObjectsState = nullptr;
	NormalStateAI* BossThrowObjectState = nullptr;
};
