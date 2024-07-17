// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AnimInstancePingu.h"
#include "PinguCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimInstancePingu::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PinguCharacter = Cast<APinguCharacter>(TryGetPawnOwner());
}

void UAnimInstancePingu::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(PinguCharacter == nullptr) return;

	FVector Velocity = PinguCharacter->GetVelocity();
	Speed = Velocity.Size();

	bIsInAir = PinguCharacter->GetCharacterMovement()->IsFalling();

	bIsInputAccelerating = PinguCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}
