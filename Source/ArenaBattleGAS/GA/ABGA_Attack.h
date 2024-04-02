// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ABGA_Attack.generated.h"

class UABComboActionData;
class UCharacterMovementComponent;
class AABCharacterBase;
/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API UABGA_Attack : public UGameplayAbility
{
    GENERATED_BODY()

    TWeakObjectPtr<AABCharacterBase> AvatarCharacter;
    TWeakObjectPtr<UCharacterMovementComponent> CharacterMovement;

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TObjectPtr<UABComboActionData> CurrentComboData;

    uint8 CurrentCombo = 0;
    FTimerHandle ComboTimerHandle;
    bool HasNextComboInput = false;

public:
    UABGA_Attack();

    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData) override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
    virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    /* 메서드 */
    FName GetNextSection();
    void StartComboTimer();
    void CheckComboInput();

    /* 이벤트 핸들링 메서드 */
    UFUNCTION()
    void OnCompleted_Event();

    UFUNCTION()
    void OnInterrupted_Event();
};
