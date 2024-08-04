// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/Machines/BossSimpleFSM.h"

#include "FiniteStateMachine/State/States/BossSearchPlayerState.h"
#include "FiniteStateMachine/State/States/BossThrowObjectState.h"
#include "FiniteStateMachine/State/States/BossThrowThreeObjectsState.h"

void BossSimpleFSM::Initialize()
{
	SearchPlayerState = new BossSearchPlayerState(SEARCH_PLAYER_STATE, this);
	ThrowObjectState = new BossThrowObjectState(THROW_OBJECT_STATE, this);
	ThrowThreeObjectsState = new BossThrowThreeObjectsState(THROW_THREE_OBJECTS_STATE, this);

	Transition(SearchPlayerState);
}
