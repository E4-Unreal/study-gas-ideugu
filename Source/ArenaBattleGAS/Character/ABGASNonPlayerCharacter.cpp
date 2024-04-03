// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASNonPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Attribute/ABGASCharacterAttributeSet.h"
#include "UI/ABGASWidgetComponent.h"

AABGASNonPlayerCharacter::AABGASNonPlayerCharacter() :
    Level(1.f)
{
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    CharacterAttributeSet = CreateDefaultSubobject<UABGASCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

    HpBar = CreateDefaultSubobject<UABGASWidgetComponent>(TEXT("HpBar"));
    HpBar->SetupAttachment(GetMesh());
    HpBar->SetRelativeLocation(FVector(0.f, 0.f, 180.f));
    static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ArenaBattle/UI/WBP_HpBar.WBP_HpBar_C'"));
    if(HpBarWidgetRef.Class)
    {
        HpBar->SetWidgetClass(HpBarWidgetRef.Class);
        HpBar->SetWidgetSpace(EWidgetSpace::Screen);
        HpBar->SetDrawSize(FVector2D(200.f, 20.f));
        HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void AABGASNonPlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // ASC 초기화
    AbilitySystem->InitAbilityActorInfo(this, this);
    CharacterAttributeSet->OnOutOfHealth.AddDynamic(this, &ThisClass::OnOutOfHealthCallBack);

    FGameplayEffectContextHandle EffectContextHandle = AbilitySystem->MakeEffectContext();
    EffectContextHandle.AddSourceObject(this);
    FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystem->MakeOutgoingSpec(CharacterAttributeSetEffect, Level, EffectContextHandle);

    if(EffectSpecHandle.IsValid())
    {
        AbilitySystem->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
    }
}

void AABGASNonPlayerCharacter::OnOutOfHealthCallBack()
{
    SetDead();
}
