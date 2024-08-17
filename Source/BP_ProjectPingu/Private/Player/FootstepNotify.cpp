// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/FootstepNotify.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PinguCharacter.h"

// Sound Stuff
void UFootstepNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (IsRunningGame())
    {
        auto *Pingu = Cast<APinguCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
        if (Pingu == nullptr)
            return;

        Pingu->PlayFootstepSound();
    }
}
