// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/ABCharacterPlayer.h"
#include "ABGASPlayerCharacter.generated.h"

struct FGameplayEventData;
class UABGASWidgetComponent;
class UAbilitySystemComponent;
class UGameplayAbility;

UCLASS()
class ARENABATTLEGAS_API AABGASPlayerCharacter : public AABCharacterPlayer, public IAbilitySystemInterface
{
    GENERATED_BODY()

    TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;

    UPROPERTY(VisibleAnywhere, Category = "Component")
    TObjectPtr<UABGASWidgetComponent> HpBar;

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

    UPROPERTY(EditAnywhere, Category = "Config")
    TMap<int32, TSubclassOf<UGameplayAbility>> DefaultInputAbilities;

    UPROPERTY(EditAnywhere, Category = "Config")
    TObjectPtr<USkeletalMesh> WeaponMesh;

    UPROPERTY(EditAnywhere, Category = "Config")
    float WeaponRange;

    UPROPERTY(EditAnywhere, Category = "Config")
    float WeaponRate;

public:
    AABGASPlayerCharacter();

    virtual void PossessedBy(AController* NewController) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    void SetupGasInputComponent();

    UFUNCTION()
    virtual void OnOutOfHealthCallBack();

    void EquipWeaponCallback(const FGameplayEventData* EventData);
    void UnequipWeaponCallback(const FGameplayEventData* EventData);

public:
    /* AbilitySystemInterface */
    FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem.Get(); }
};
