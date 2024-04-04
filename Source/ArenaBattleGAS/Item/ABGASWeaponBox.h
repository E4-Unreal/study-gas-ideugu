// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABGASItemBox.h"
#include "ABGASWeaponBox.generated.h"

UCLASS()
class ARENABATTLEGAS_API AABGASWeaponBox : public AABGASItemBox
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    FGameplayTag WeaponEventTag;

protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
