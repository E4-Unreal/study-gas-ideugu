// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGASHealthBar.h"

#include "AbilitySystemComponent.h"
#include "Attribute/ABGASCharacterAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UABGASHealthBar::SetOwner(AActor* InOwner)
{
    Super::SetOwner(InOwner);

    UAbilitySystemComponent* LocalAbilitySystem = GetAbilitySystem();
    if(!LocalAbilitySystem) return;

    FGameplayAttribute HealthAttribute = UABGASCharacterAttributeSet::GetHealthAttribute();
    if(LocalAbilitySystem->HasAttributeSetForAttribute(HealthAttribute))
    {
        // 이벤트 바인딩
        LocalAbilitySystem->GetGameplayAttributeValueChangeDelegate(HealthAttribute)
        .AddUObject(this, &ThisClass::OnHealthChanged);

        // 초기화
        CurrentHealth = LocalAbilitySystem->GetNumericAttribute(HealthAttribute);
    }

    FGameplayAttribute MaxHealthAttribute = UABGASCharacterAttributeSet::GetMaxHealthAttribute();
    if(LocalAbilitySystem->HasAttributeSetForAttribute(MaxHealthAttribute))
    {
        // 이벤트 바인딩
        LocalAbilitySystem->GetGameplayAttributeValueChangeDelegate(MaxHealthAttribute)
        .AddUObject(this, &ThisClass::OnMaxHealthChanged);

        // 초기화
        CurrentMaxHealth = LocalAbilitySystem->GetNumericAttribute(MaxHealthAttribute);
    }

    UpdateHpBar();
}

void UABGASHealthBar::OnHealthChanged(const FOnAttributeChangeData& ChangeData)
{
    CurrentHealth = ChangeData.NewValue;
    UpdateHpBar();
}

void UABGASHealthBar::OnMaxHealthChanged(const FOnAttributeChangeData& ChangeData)
{
    CurrentMaxHealth = ChangeData.NewValue;
    UpdateHpBar();
}

void UABGASHealthBar::UpdateHpBar() const
{
    if(PbHpBar)
    {
        float HealthRatio = FMath::IsNearlyZero(CurrentMaxHealth) ? 0.f : CurrentHealth / CurrentMaxHealth;
        PbHpBar->SetPercent(HealthRatio);
    }

    if(TxtHpStat)
    {
        TxtHpStat->SetText(FText::FromString(FString::Printf(TEXT("%0.f/%0.f"), CurrentHealth, CurrentMaxHealth)));
    }
}
