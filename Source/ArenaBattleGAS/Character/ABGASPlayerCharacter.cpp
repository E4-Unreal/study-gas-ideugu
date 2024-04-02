// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Player/ABGASPlayerState.h"

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
        int32 InputID = 0;
        for(const auto& DefaultAbility : DefaultAbilities)
        {
            FGameplayAbilitySpec GameplayAbilitySpec = AbilitySystem->BuildAbilitySpecFromClass(DefaultAbility);
            GameplayAbilitySpec.InputID = InputID;
            AbilitySystem->GiveAbility(GameplayAbilitySpec);

            InputID++;
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
    }
}
