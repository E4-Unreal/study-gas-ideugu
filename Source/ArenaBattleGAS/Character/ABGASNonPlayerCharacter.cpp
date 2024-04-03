// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASNonPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Attribute/ABGASCharacterAttributeSet.h"

AABGASNonPlayerCharacter::AABGASNonPlayerCharacter() :
    Level(1.f)
{
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    CharacterAttributeSet = CreateDefaultSubobject<UABGASCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
}

void AABGASNonPlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // ASC 초기화
    AbilitySystem->InitAbilityActorInfo(this, this);

    FGameplayEffectContextHandle EffectContextHandle = AbilitySystem->MakeEffectContext();
    EffectContextHandle.AddSourceObject(this);
    FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystem->MakeOutgoingSpec(CharacterAttributeSetEffect, Level, EffectContextHandle);

    if(EffectSpecHandle.IsValid())
    {
        AbilitySystem->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
    }
}
