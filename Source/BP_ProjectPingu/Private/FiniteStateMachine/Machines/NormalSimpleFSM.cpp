// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/Machines/NormalSimpleFSM.h"
#include "FiniteStateMachine/State/States/BossThrowObjectState.h"
#include "FiniteStateMachine/State/States/BossThrowThreeObjectsState.h"
#include "FiniteStateMachine/State/States/NormalSearchPlayerState.h"
#include "FiniteStateMachine/State/States/NormalThrowObjectState.h"

void NormalSimpleFSM::Initialize()
{
	SearchPlayerState = new NormalSearchPlayerState(SEARCH_PLAYER_STATE, this);
	ThrowObjectState = new NormalThrowObjectState(THROW_OBJECT_STATE, this);
	ThrowThreeObjectsState = new BossThrowThreeObjectsState(THROW_THREE_OBJECTS_STATE, this);
	BossThrowObjectState = new ::BossThrowObjectState(BOSS_THROW_OBJECT_STATE, this);

	Transition(SearchPlayerState);
}

