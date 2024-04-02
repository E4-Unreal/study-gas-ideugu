// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASFountain.h"

#include "AbilitySystemComponent.h"
#include "GA/ABGA_Rotate.h"
#include "GameFramework/RotatingMovementComponent.h"

AABGASFountain::AABGASFountain()
{
    RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    ActionPeriod = 3.f;
}

void AABGASFountain::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    RotatingMovement->bAutoActivate = false;
    RotatingMovement->Deactivate();

    // ASC 초기화 및 GA 부여
    AbilitySystem->InitAbilityActorInfo(this, this);
    AbilitySystem->GiveAbility(AbilitySystem->BuildAbilitySpecFromClass(UABGA_Rotate::StaticClass()));
}

void AABGASFountain::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(ActionTimer, this, &ThisClass::TimerAction, ActionPeriod, true, 0.f);
}

void AABGASFountain::TimerAction()
{
    if(FGameplayAbilitySpec* RotateSpec = AbilitySystem->FindAbilitySpecFromClass(UABGA_Rotate::StaticClass()))
    {
        if(RotateSpec->IsActive())
            AbilitySystem->CancelAbilityHandle(RotateSpec->Handle);
        else
            AbilitySystem->TryActivateAbility(RotateSpec->Handle);
    }
}
