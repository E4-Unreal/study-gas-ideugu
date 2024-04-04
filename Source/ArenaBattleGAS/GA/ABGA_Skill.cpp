// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGA_Skill.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/ABGASPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UABGA_Skill::UABGA_Skill()
{
}

void UABGA_Skill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    AABGASPlayerCharacter* Character = Cast<AABGASPlayerCharacter>(ActorInfo->AvatarActor.Get());
    if(!Character) return;

    ActiveSkillActionMontage = Character->GetSkillAnimMontage();
    if(!ActiveSkillActionMontage) return;

    CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);

    Character->GetCharacterMovement()->SetMovementMode(MOVE_None);

    UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("Skill"), ActiveSkillActionMontage);
    PlayMontageTask->OnCompleted.AddDynamic(this, &ThisClass::OnCompleted_Event);
    PlayMontageTask->OnInterrupted.AddDynamic(this, &ThisClass::OnInterrupted_Event);
    PlayMontageTask->ReadyForActivation();
}

void UABGA_Skill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    AABGASPlayerCharacter* Character = Cast<AABGASPlayerCharacter>(ActorInfo->AvatarActor.Get());
    if(!Character) return;

    Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UABGA_Skill::OnCompleted_Event()
{
    bool bReplicatedEndAbility = true;
    bool bWasCancelled = false;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UABGA_Skill::OnInterrupted_Event()
{
    bool bReplicatedEndAbility = true;
    bool bWasCancelled = true;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
