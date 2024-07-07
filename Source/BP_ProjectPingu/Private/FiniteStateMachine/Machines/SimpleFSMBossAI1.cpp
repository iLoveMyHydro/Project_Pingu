// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/Machines/SimpleFSMBossAI1.h"
#include "FiniteStateMachine/State/States/SearchPlayerStateBossAI1.h"
#include "FiniteStateMachine/State/States/ThrowBouncingObjectStateBossAI1.h"
#include "FiniteStateMachine/State/States/ThrowManyObjectsStateBossAI1.h"
#include "FiniteStateMachine/State/States/ThrowObjectStateBossAI1.h"
#include "FiniteStateMachine/State/States/WaitStateBossAI1.h"


void SimpleFSMBossAI1::Initialize()
{
	SearchPlayerState = new SearchPlayerStateBossAI1(SEARCH_PLAYER_STATE, this);
	ThrowObjectState = new ThrowObjectStateBossAI1(THROW_OBJECT_STATE, this);
	WaitState = new WaitStateBossAI1(WAIT_STATE, this);
	ThrowManyObjectsState = new ThrowManyObjectsStateBossAI1(THROW_MANY_OBJECTS_STATE, this);
	ThrowBouncingObjectState = new ThrowBouncingObjectStateBossAI1(THROW_BOUNCING_OBJECTS_STATE, this);

	Transition(SearchPlayerState);
	Transition(WaitState);
	//TODO:
}

