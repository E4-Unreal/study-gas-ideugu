// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Prop/ABFountain.h"
#include "ABGASFountain.generated.h"

class UAbilitySystemComponent;
class URotatingMovementComponent;

UCLASS()
class ARENABATTLEGAS_API AABGASFountain : public AABFountain, public IAbilitySystemInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, Category = "Component")
    TObjectPtr<URotatingMovementComponent> RotatingMovement;

    UPROPERTY(VisibleAnywhere, Category = "Component")
    TObjectPtr<UAbilitySystemComponent> AbilitySystem;

    UPROPERTY(EditAnywhere, Category = "Config")
    float ActionPeriod;

    FTimerHandle ActionTimer;

public:
    AABGASFountain();

protected:
    /* Actor */
    virtual void PostInitializeComponents() override;
    virtual void BeginPlay() override;

    virtual void TimerAction();

public:
    /* AbilitySystemInterface */
    FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }
};
