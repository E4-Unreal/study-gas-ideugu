// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ABCharacterSkillAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API UABCharacterSkillAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    ATTRIBUTE_ACCESSORS(ThisClass, SkillRange)
    ATTRIBUTE_ACCESSORS(ThisClass, MaxSkillRange)
    ATTRIBUTE_ACCESSORS(ThisClass, SkillRate)
    ATTRIBUTE_ACCESSORS(ThisClass, MaxSkillRate)
    ATTRIBUTE_ACCESSORS(ThisClass, SkillEnergy)
    ATTRIBUTE_ACCESSORS(ThisClass, MaxSkillEnergy)

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData SkillRange;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData MaxSkillRange;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData SkillRate;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData MaxSkillRate;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData SkillEnergy;

    UPROPERTY(BlueprintReadOnly, Category = "Attack")
    FGameplayAttributeData MaxSkillEnergy;

public:
    UABCharacterSkillAttributeSet();

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
