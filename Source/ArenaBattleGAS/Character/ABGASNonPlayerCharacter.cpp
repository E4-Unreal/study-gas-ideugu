// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASNonPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Attribute/ABGASCharacterAttributeSet.h"

AABGASNonPlayerCharacter::AABGASNonPlayerCharacter()
{
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    CharacterAttributeSet = CreateDefaultSubobject<UABGASCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
}

void AABGASNonPlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // ASC 초기화
    AbilitySystem->InitAbilityActorInfo(this, this);
}
