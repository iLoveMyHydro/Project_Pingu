// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/BossFSM.h"

/**
 * 
 */
class BossStateAI
{
public:
	inline BossStateAI() {};
	inline BossStateAI(const FString& A_Name, BossFSM* A_Machine) : Name(A_Name), Machine(A_Machine) {};
	inline virtual ~BossStateAI() {};

	virtual void Enter(void);
	virtual void Tick(float A_DeltaTime);
	virtual void Exit(void);

	inline const FString GetName() { return Name; }

protected:
	FString Name = FString(TEXT(""));
	BossFSM* Machine = nullptr;
};
