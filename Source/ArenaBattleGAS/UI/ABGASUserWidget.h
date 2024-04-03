// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Blueprint/UserWidget.h"
#include "ABGASUserWidget.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API UABGASUserWidget : public UUserWidget, public IAbilitySystemInterface
{
    GENERATED_BODY()

    TObjectPtr<UAbilitySystemComponent> AbilitySystem;

public:
    virtual void SetOwner(AActor* InOwner);

protected:
    UFUNCTION(BlueprintCallable)
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }

public:
    /* AbilitySystemInterface */
    FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem.Get(); };
};
