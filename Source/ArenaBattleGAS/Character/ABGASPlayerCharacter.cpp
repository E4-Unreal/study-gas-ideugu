// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Player/ABGASPlayerState.h"

AABGASPlayerCharacter::AABGASPlayerCharacter()
{
    static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattleGAS/Animation/AM_ComboAttack.AM_ComboAttack'"));
    if (ComboActionMontageRef.Object)
    {
    	ComboActionMontage = ComboActionMontageRef.Object;
    }
}

void AABGASPlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if(AABGASPlayerState* PS = GetPlayerState<AABGASPlayerState>())
    {
        // ASC 레퍼런스 주입
        AbilitySystem = PS->GetAbilitySystemComponent();

        // ASC 초기화
        AbilitySystem->InitAbilityActorInfo(PS, this);

        // 기본 GA 부여
        for(const auto& DefaultAbility : DefaultAbilities)
        {
            FGameplayAbilitySpec GameplayAbilitySpec = AbilitySystem->BuildAbilitySpecFromClass(DefaultAbility);
            AbilitySystem->GiveAbility(GameplayAbilitySpec);
        }

        // 기본 입력 GA 부여
        for (const auto& [DefaultInputID, DefaultAbility] : DefaultInputAbilities)
        {
            FGameplayAbilitySpec GameplayAbilitySpec = AbilitySystem->BuildAbilitySpecFromClass(DefaultAbility);
            GameplayAbilitySpec.InputID = DefaultInputID;
            AbilitySystem->GiveAbility(GameplayAbilitySpec);
        }
    }
}

void AABGASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    SetupGasInputComponent();
}

void AABGASPlayerCharacter::SetupGasInputComponent()
{
    if(AbilitySystem.IsValid() && IsValid(InputComponent))
    {
        UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, AbilitySystem.Get(), &UAbilitySystemComponent::PressInputID, 0);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, AbilitySystem.Get(), &UAbilitySystemComponent::ReleaseInputID, 0);
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, AbilitySystem.Get(), &UAbilitySystemComponent::PressInputID, 1);
    }
}
