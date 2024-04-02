// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASFountain.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Tag/ABGameplayTag.h"

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

    // ASC 초기화
    AbilitySystem->InitAbilityActorInfo(this, this);

    // 기본 GA 부여
    for(const auto& DefaultAbility : DefaultAbilities)
    {
        AbilitySystem->GiveAbility(AbilitySystem->BuildAbilitySpecFromClass(DefaultAbility));
    }
}

void AABGASFountain::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(ActionTimer, this, &ThisClass::TimerAction, ActionPeriod, true, 0.f);
}

void AABGASFountain::TimerAction()
{
    using namespace ABGameplayTags::Actor;

    const FGameplayTagContainer TargetTag(Action::Rotate);
    if(!AbilitySystem->HasMatchingGameplayTag(State::Rotating))
        AbilitySystem->TryActivateAbilitiesByTag(TargetTag);
    else
        AbilitySystem->CancelAbilities(&TargetTag);
}
