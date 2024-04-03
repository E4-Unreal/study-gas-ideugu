// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ABGASCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOutOfHealthDelegate);

/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API UABGASCharacterAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    ATTRIBUTE_ACCESSORS(ThisClass, AttackRange)
    ATTRIBUTE_ACCESSORS(ThisClass, MaxAttackRange)
    ATTRIBUTE_ACCESSORS(ThisClass, AttackRadius)
    ATTRIBUTE_ACCESSORS(ThisClass, MaxAttackRadius)
    ATTRIBUTE_ACCESSORS(ThisClass, AttackRate)
    ATTRIBUTE_ACCESSORS(ThisClass, MaxAttackRate)
    ATTRIBUTE_ACCESSORS(ThisClass, Health)
    ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth)
    ATTRIBUTE_ACCESSORS(ThisClass, Damage)

    mutable FOutOfHealthDelegate OnOutOfHealth;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData AttackRange;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData MaxAttackRange;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData AttackRadius;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData MaxAttackRadius;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData AttackRate;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData MaxAttackRate;

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData Health;

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData MaxHealth;

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData Damage;

    bool bOutOfHealth;

public:
    UABGASCharacterAttributeSet();

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
    virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
