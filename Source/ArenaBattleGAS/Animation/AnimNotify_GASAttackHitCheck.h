﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GASAttackHitCheck.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API UAnimNotify_GASAttackHitCheck : public UAnimNotify
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere)
    FGameplayTag TriggerTag;

    UPROPERTY(EditAnywhere)
    float ComboAttackLevel;

public:
    UAnimNotify_GASAttackHitCheck();

protected:
    virtual FString GetNotifyName_Implementation() const override;
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
