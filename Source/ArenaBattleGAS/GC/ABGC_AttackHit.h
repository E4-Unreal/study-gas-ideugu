// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "ABGC_AttackHit.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API UABGC_AttackHit : public UGameplayCueNotify_Static
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TObjectPtr<UParticleSystem> ParticleSystem;

public:
    UABGC_AttackHit();

    virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
};
