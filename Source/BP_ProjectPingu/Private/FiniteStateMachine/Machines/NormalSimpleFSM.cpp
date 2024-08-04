// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/Machines/NormalSimpleFSM.h"
#include "FiniteStateMachine/State/States/NormalSearchPlayerState.h"
#include "FiniteStateMachine/State/States/NormalThrowObjectState.h"

void NormalSimpleFSM::Initialize()
{
	SearchPlayerState = new NormalSearchPlayerState(SEARCH_PLAYER_STATE, this);
	ThrowObjectState = new NormalThrowObjectState(THROW_OBJECT_STATE, this);

	Transition(SearchPlayerState);
}

