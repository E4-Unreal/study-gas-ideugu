// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ABGA_Rotate.generated.h"

// TODO 타이머 기능도 게임플레이 어빌리티에서 설정하는 것이 낫지 않을까?
/**
 * 분수대 회전 어빌리티
 */
UCLASS()
class ARENABATTLEGAS_API UABGA_Rotate : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UABGA_Rotate();

    /* GameplayAbility */
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
};
