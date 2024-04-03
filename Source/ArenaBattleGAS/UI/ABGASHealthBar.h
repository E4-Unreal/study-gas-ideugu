// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABGASUserWidget.h"
#include "Attribute/ABGASCharacterAttributeSet.h"
#include "ABGASHealthBar.generated.h"

class UProgressBar;
class UTextBlock;

/**
 *
 */
UCLASS()
class ARENABATTLEGAS_API UABGASHealthBar : public UABGASUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> PbHpBar;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TxtHpStat;

    float CurrentHealth;
    float CurrentMaxHealth;

protected:
    virtual void SetOwner(AActor* InOwner) override;

    virtual void OnHealthChanged(const FOnAttributeChangeData& ChangeData);
    virtual void OnMaxHealthChanged(const FOnAttributeChangeData& ChangeData);

    void UpdateHpBar() const;
};
