// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Controller/BossAIController.h"
#include "FiniteStateMachine/FSM/BossFSM.h"

/**
 * 
 */
class BossSimpleFSM : public BossFSM
{
public:
	inline BossSimpleFSM(ABossAIController* A_Controller) : BossFSM(A_Controller) {};
	inline ~BossSimpleFSM() {};

	virtual void Initialize() override;

	BossStateAI* GetSearchPlayerState(void) const { return SearchPlayerState; }
	BossStateAI* GetThrowObjectState(void) const { return ThrowObjectState; }
	BossStateAI* GetThrowThreeObjectsState(void) const { return ThrowThreeObjectsState; }

private:
	const FString SEARCH_PLAYER_STATE = FString(TEXT("Search Player State"));
	const FString THROW_OBJECT_STATE = FString(TEXT("Throw Object State"));
	const FString THROW_THREE_OBJECTS_STATE = FString(TEXT("Throw Three Objects State"));

	//States
	BossStateAI* SearchPlayerState = nullptr;
	BossStateAI* ThrowObjectState = nullptr;
	BossStateAI* ThrowThreeObjectsState = nullptr;
};
