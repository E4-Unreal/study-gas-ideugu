// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ABAT_WaitForTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

class AABTA_Trace;
/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API UABAT_WaitForTrace : public UAbilityTask
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FTraceResultDelegate OnComplete;

protected:
    UPROPERTY()
    TSubclassOf<AABTA_Trace> TargetActorClass;

    UPROPERTY()
    TObjectPtr<AABTA_Trace> SpawnedTargetActor;

public:
    UABAT_WaitForTrace();

    UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName="WaitForTrace",
        HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
    static UABAT_WaitForTrace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AABTA_Trace> InTargetActorClass);

    virtual void Activate() override;
    virtual void OnDestroy(bool bInOwnerFinished) override;

protected:
    /* 메서드 */
    void SpawnAndInitializeTargetActor();
    void FinalizeTargetActor();

    /* 이벤트 핸들링 메서드 */
    void OnTargetDataReady_Event(const FGameplayAbilityTargetDataHandle& DataHandle);
};
