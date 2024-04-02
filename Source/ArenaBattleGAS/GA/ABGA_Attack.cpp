// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGA_Attack.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/ABCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"


UABGA_Attack::UABGA_Attack()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UABGA_Attack::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    // 레퍼런스 캐싱
    AvatarCharacter = Cast<AABCharacterBase>(GetAvatarActorFromActorInfo());
    CharacterMovement = AvatarCharacter->GetCharacterMovement();

    check(AvatarCharacter.Get())
    check(CharacterMovement.Get())
}

void UABGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // 캐릭터 정지
    CharacterMovement->SetMovementMode(MOVE_None);

    // 몽타주 재생 어빌리티 태스크 생성 및 실행
    UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), AvatarCharacter->GetComboActionMontage());
    PlayAttackTask->OnCompleted.AddDynamic(this, &ThisClass::OnCompleted_Event);
    PlayAttackTask->OnInterrupted.AddDynamic(this, &ThisClass::OnInterrupted_Event);
    PlayAttackTask->ReadyForActivation();
}

void UABGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void UABGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
    Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UABGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // 캐릭터 정지
    CharacterMovement->SetMovementMode(MOVE_Walking);
}

void UABGA_Attack::OnCompleted_Event()
{
    bool bReplicatedEndAbility = true;
    bool bWasCancelled = false;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UABGA_Attack::OnInterrupted_Event()
{
    bool bReplicatedEndAbility = true;
    bool bWasCancelled = true;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
