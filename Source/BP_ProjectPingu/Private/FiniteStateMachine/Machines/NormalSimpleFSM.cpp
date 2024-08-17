// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/Machines/NormalSimpleFSM.h"
#include "FiniteStateMachine/State/States/BossThrowObjectState.h"
#include "FiniteStateMachine/State/States/BossThrowFastObjectState.h"
#include "FiniteStateMachine/State/States/NormalSearchPlayerState.h"
#include "FiniteStateMachine/State/States/NormalThrowObjectState.h"

// Initialize the FSM
void NormalSimpleFSM::Initialize()
{
	SearchPlayerState = new NormalSearchPlayerState(SEARCH_PLAYER_STATE, this);
	ThrowObjectState = new NormalThrowObjectState(THROW_OBJECT_STATE, this);
	ThrowFastObjectsState = new BossThrowFastObjectsState(THROW_FAST_OBJECTS_STATE, this);
	BossThrowObjectState = new ::BossThrowObjectState(BOSS_THROW_OBJECT_STATE, this);

	Transition(SearchPlayerState);
}

