// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGA_Jump.h"

#include "AT/ABAT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"

UABGA_Jump::UABGA_Jump()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UABGA_Jump::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    // 레퍼런스 할당
    AvatarCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());

    check(AvatarCharacter.Get());
}

bool UABGA_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
    FGameplayTagContainer* OptionalRelevantTags) const
{
    if(!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) return false;

    return AvatarCharacter->CanJump();
}

void UABGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    UABAT_JumpAndWaitForLanding* JumpAndWaitForLandingTask = UABAT_JumpAndWaitForLanding::CreateTask(this);
    JumpAndWaitForLandingTask->OnComplete.AddDynamic(this, &ThisClass::OnLanded_Event);
    JumpAndWaitForLandingTask->ReadyForActivation();
}

void UABGA_Jump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo)
{
    AvatarCharacter->StopJumping();
}

void UABGA_Jump::OnLanded_Event()
{
    bool bReplicatedEndAbility = true;
    bool bWasCancelled = true;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);

}
