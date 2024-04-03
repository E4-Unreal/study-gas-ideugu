// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGASCharacterAttributeSet.h"

#include "ArenaBattleGAS.h"
#include "GameplayEffectExtension.h"
#include "Tag/ABGameplayTag.h"

UABGASCharacterAttributeSet::UABGASCharacterAttributeSet() :
    AttackRange(100.f),
    AttackRadius(50.f),
    AttackRate(30.f),
    MaxAttackRange(300.f),
    MaxAttackRadius(150.f),
    MaxAttackRate(100.f),
    MaxHealth(100.f),
    Damage(0.f)
{
    InitHealth(GetMaxHealth());
}

void UABGASCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if(Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    }
    else if(Attribute == GetDamageAttribute())
    {
        NewValue = FMath::Max(0.f, NewValue);

        if(GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(ABGameplayTags::Character::State::Invincible))
            NewValue = 0;
    }
}

void UABGASCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
    float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

bool UABGASCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
    return Super::PreGameplayEffectExecute(Data);
}

void UABGASCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if(Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        UE_LOG(LogABGAS, Warning, TEXT("Direct Health Access : %f"), GetHealth())
    }
    else if(Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        UE_LOG(LogABGAS, Log, TEXT("Damage : %f"), GetDamage())
        SetHealth(GetHealth() - GetDamage());
        SetDamage(0.f);
    }

    // 죽음 처리
    if(!bOutOfHealth && FMath::IsNearlyZero(GetHealth()))
    {
        Data.Target.AddLooseGameplayTag(ABGameplayTags::Character::State::Dead);
        bOutOfHealth = true;
        OnOutOfHealth.Broadcast();
    }
}
