// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGASUserWidget.h"

#include "AbilitySystemGlobals.h"

void UABGASUserWidget::SetOwner(AActor* InOwner)
{
    AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InOwner);
}
