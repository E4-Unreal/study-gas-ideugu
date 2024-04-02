// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/ABCharacterPlayer.h"
#include "ABGASPlayerCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;

UCLASS()
class ARENABATTLEGAS_API AABGASPlayerCharacter : public AABCharacterPlayer, public IAbilitySystemInterface
{
    GENERATED_BODY()

    TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

    UPROPERTY(EditAnywhere, Category = "Config")
    TMap<int32, TSubclassOf<UGameplayAbility>> DefaultInputAbilities;

public:
    AABGASPlayerCharacter();

    virtual void PossessedBy(AController* NewController) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    void SetupGasInputComponent();

public:
    /* AbilitySystemInterface */
    FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem.Get(); }
};
