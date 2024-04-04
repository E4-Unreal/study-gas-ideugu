// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ABGA_Skill.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API UABGA_Skill : public UGameplayAbility
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TObjectPtr<UAnimMontage> ActiveSkillActionMontage;

public:
    UABGA_Skill();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    /* 이벤트 핸들링 메서드 */
    UFUNCTION()
    void OnCompleted_Event();

    UFUNCTION()
    void OnInterrupted_Event();
};
