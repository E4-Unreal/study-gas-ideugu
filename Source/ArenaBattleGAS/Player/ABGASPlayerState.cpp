// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGASPlayerState.h"

#include "AbilitySystemComponent.h"

AABGASPlayerState::AABGASPlayerState()
{
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    AbilitySystem->SetIsReplicated(true);
}
