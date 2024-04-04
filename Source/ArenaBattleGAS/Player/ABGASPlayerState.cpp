// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGASPlayerState.h"

#include "AbilitySystemComponent.h"
#include "Attribute/ABCharacterSkillAttributeSet.h"
#include "Attribute/ABGASCharacterAttributeSet.h"

AABGASPlayerState::AABGASPlayerState()
{
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    AbilitySystem->SetIsReplicated(true);

    CharacterAttributeSet = CreateDefaultSubobject<UABGASCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
    CharacterSkillAttributeSet = CreateDefaultSubobject<UABCharacterSkillAttributeSet>(TEXT("CharacterSkillAttributeSet"));
}
