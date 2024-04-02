// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/ABFountain.h"
#include "ABGASFountain.generated.h"

class URotatingMovementComponent;

UCLASS()
class ARENABATTLEGAS_API AABGASFountain : public AABFountain
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, Category = "Component")
    TObjectPtr<URotatingMovementComponent> RotatingMovement;

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
};
