// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/ABCharacterNonPlayer.h"
#include "ABGASNonPlayerCharacter.generated.h"

class UGameplayEffect;
class UABGASCharacterAttributeSet;
class UABGASWidgetComponent;

UCLASS()
class ARENABATTLEGAS_API AABGASNonPlayerCharacter : public AABCharacterNonPlayer, public IAbilitySystemInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetAbilitySystem, Category = "Component")
    TObjectPtr<UAbilitySystemComponent> AbilitySystem;

    UPROPERTY()
    TObjectPtr<UABGASCharacterAttributeSet> CharacterAttributeSet;

    UPROPERTY(VisibleAnywhere, Category = "Component")
    TObjectPtr<UABGASWidgetComponent> HpBar;

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<UGameplayEffect> CharacterAttributeSetEffect;

    UPROPERTY(EditAnywhere, Category = "Config")
    float Level;

public:
    AABGASNonPlayerCharacter();

    virtual void PossessedBy(AController* NewController) override;

public:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }

public:
    /* AbilitySystemInterface */
    FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem.Get(); }
};
