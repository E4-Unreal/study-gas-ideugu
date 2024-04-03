// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGE_AttackDamage.h"

#include "Attribute/ABGASCharacterAttributeSet.h"

UABGE_AttackDamage::UABGE_AttackDamage()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo HealthModifier;
    HealthModifier.Attribute = UABGASCharacterAttributeSet::GetHealthAttribute();
    HealthModifier.ModifierOp = EGameplayModOp::Additive;
    HealthModifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(-30.f);

    Modifiers.Add(HealthModifier);
}
