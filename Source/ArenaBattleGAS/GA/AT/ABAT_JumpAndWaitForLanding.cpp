// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAT_JumpAndWaitForLanding.h"

#include "GameFramework/Character.h"

UABAT_JumpAndWaitForLanding::UABAT_JumpAndWaitForLanding()
{
}

UABAT_JumpAndWaitForLanding* UABAT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
    UABAT_JumpAndWaitForLanding* NewTask = NewAbilityTask<UABAT_JumpAndWaitForLanding>(OwningAbility);

    return NewTask;
}

void UABAT_JumpAndWaitForLanding::Activate()
{
    Super::Activate();

    AvatarCharacter = CastChecked<ACharacter>(GetAvatarActor());
    AvatarCharacter->Jump();
    AvatarCharacter->LandedDelegate.AddDynamic(this, &ThisClass::OnLanded_Event);

    SetWaitingOnAvatar();
}

void UABAT_JumpAndWaitForLanding::OnDestroy(bool bInOwnerFinished)
{
    AvatarCharacter->LandedDelegate.RemoveDynamic(this, &ThisClass::OnLanded_Event);

    Super::OnDestroy(bInOwnerFinished);
}

void UABAT_JumpAndWaitForLanding::OnLanded_Event(const FHitResult& Hit)
{
    if(ShouldBroadcastAbilityTaskDelegates())
        OnComplete.Broadcast();
}
