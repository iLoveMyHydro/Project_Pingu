// Fill out your copyright notice in the Description page of Project Settings.

//This Notify was sponsored by Hubsi

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FootstepNotify.generated.h"

/**
 * 
 */
UCLASS()
class UFootstepNotify : public UAnimNotify
{
	GENERATED_BODY()
	
protected:

	// Sound Stuff
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
