// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine/Machines/SimpleFSMAI1.h"
#include "FiniteStateMachine/State/States/SearchPlayerStateAI1.h"
#include "FiniteStateMachine/State/States/ThrowObjectStateAI1.h"

void SimpleFSMAI1::Initialize()
{
	SearchPlayerState = new SearchPlayerStateAI1(SEARCH_PLAYER_STATE, this);
	ThrowObjectState = new ThrowObjectStateAI1(THROW_OBJECT_STATE, this);

	Transition(SearchPlayerState);
}

