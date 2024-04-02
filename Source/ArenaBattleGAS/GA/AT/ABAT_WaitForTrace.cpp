// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAT_WaitForTrace.h"

#include "AbilitySystemComponent.h"
#include "GA/TA/ABTA_Trace.h"

UABAT_WaitForTrace::UABAT_WaitForTrace()
{
}

UABAT_WaitForTrace* UABAT_WaitForTrace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AABTA_Trace> InTargetActorClass)
{
    UABAT_WaitForTrace* NewTask = NewAbilityTask<UABAT_WaitForTrace>(OwningAbility);
    NewTask->TargetActorClass = InTargetActorClass;

    return NewTask;
}

void UABAT_WaitForTrace::Activate()
{
    Super::Activate();

    SpawnAndInitializeTargetActor();
    FinalizeTargetActor();

    SetWaitingOnAvatar();
}

void UABAT_WaitForTrace::OnDestroy(bool bInOwnerFinished)
{
    Super::OnDestroy(bInOwnerFinished);

    if(SpawnedTargetActor) SpawnedTargetActor->Destroy();
}

void UABAT_WaitForTrace::SpawnAndInitializeTargetActor()
{
    SpawnedTargetActor = GetWorld()->SpawnActorDeferred<AABTA_Trace>(TargetActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if(SpawnedTargetActor)
    {
        SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &ThisClass::OnTargetDataReady_Event);
    }
}

void UABAT_WaitForTrace::FinalizeTargetActor()
{
    if(AbilitySystemComponent.IsValid())
    {
        const FTransform SpawnTransform = AbilitySystemComponent->GetAvatarActor()->GetTransform();
        SpawnedTargetActor->FinishSpawning(SpawnTransform);

        AbilitySystemComponent->SpawnedTargetActors.Push(SpawnedTargetActor);
        SpawnedTargetActor->StartTargeting(Ability);
        SpawnedTargetActor->ConfirmTargeting();
    }
}

void UABAT_WaitForTrace::OnTargetDataReady_Event(const FGameplayAbilityTargetDataHandle& DataHandle)
{
    if(ShouldBroadcastAbilityTaskDelegates())
    {
        OnComplete.Broadcast(DataHandle);
    }

    EndTask();
}
