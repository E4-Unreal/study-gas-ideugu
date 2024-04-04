// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "ABGASPlayerState.generated.h"

class UABCharacterSkillAttributeSet;
class UAbilitySystemComponent;
class UABGASCharacterAttributeSet;

/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API AABGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetAbilitySystem, Category = "Component")
    TObjectPtr<UAbilitySystemComponent> AbilitySystem;

    UPROPERTY()
    TObjectPtr<UABGASCharacterAttributeSet> CharacterAttributeSet;

    UPROPERTY()
    TObjectPtr<UABCharacterSkillAttributeSet> CharacterSkillAttributeSet;

public:
    AABGASPlayerState();

protected:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }

public:
    /* AbilitySystemInterface */
    FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; }
};
