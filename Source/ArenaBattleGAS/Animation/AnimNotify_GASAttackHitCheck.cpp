// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_GASAttackHitCheck.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

UAnimNotify_GASAttackHitCheck::UAnimNotify_GASAttackHitCheck()
{
}

FString UAnimNotify_GASAttackHitCheck::GetNotifyName_Implementation() const
{
    return TEXT("GASAttackHitCheck");
}

void UAnimNotify_GASAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
    const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if(MeshComp)
    {
        if(AActor* OwnerActor = MeshComp->GetOwner())
        {
            FGameplayEventData PayloadData;
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerTag, PayloadData);
        }
    }
}
