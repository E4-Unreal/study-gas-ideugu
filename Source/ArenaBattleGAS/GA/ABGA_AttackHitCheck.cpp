// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGA_AttackHitCheck.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"
#include "AT/ABAT_WaitForTrace.h"
#include "Attribute/ABGASCharacterAttributeSet.h"
#include "TA/ABTA_Trace.h"
#include "Tag/ABGameplayTag.h"

UABGA_AttackHitCheck::UABGA_AttackHitCheck()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UABGA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // 콤보 공격 레벨 지정
    CurrentLevel = TriggerEventData->EventMagnitude;

    UABAT_WaitForTrace* WaitForTraceTask = UABAT_WaitForTrace::CreateTask(this, AABTA_Trace::StaticClass());
    WaitForTraceTask->OnComplete.AddDynamic(this, &ThisClass::OnTraceResultCallBack);
    WaitForTraceTask->ReadyForActivation();
}

void UABGA_AttackHitCheck::OnTraceResultCallBack(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
    if(UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
    {
        FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);

        UE_LOG(LogTemp, Error, TEXT("Target %s Detected"), *(HitResult.GetActor()->GetName()))

        const UABGASCharacterAttributeSet* SourceAttribute = GetAbilitySystemComponentFromActorInfo_Checked()->GetSet<UABGASCharacterAttributeSet>();

        FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect, CurrentLevel);
        if(EffectSpecHandle.IsValid())
        {
            EffectSpecHandle.Data->SetSetByCallerMagnitude(ABGameplayTags::Data::Damage, -SourceAttribute->GetAttackRate());
            ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
        }
    }

    bool bReplicatedEndAbility = true;
    bool bWasCancelled = true;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
