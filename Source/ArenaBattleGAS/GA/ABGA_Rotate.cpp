// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGA_Rotate.h"

#include "GameFramework/RotatingMovementComponent.h"
#include "Tag/ABGameplayTag.h"

UABGA_Rotate::UABGA_Rotate()
{
    // 어빌리티 태그 설정
    using namespace ABGameplayTags::Actor;
    AbilityTags.AddTagFast(Action::Rotate);
    ActivationOwnedTags.AddTagFast(State::Rotating);
}

void UABGA_Rotate::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if(AActor* AvatarActor = GetAvatarActorFromActorInfo())
    {
        if(URotatingMovementComponent* RotatingMovement = Cast<URotatingMovementComponent>(AvatarActor->GetComponentByClass(URotatingMovementComponent::StaticClass())))
        {
            RotatingMovement->Activate(true);
        }
    }
}

void UABGA_Rotate::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
    Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

    if(AActor* AvatarActor = GetAvatarActorFromActorInfo())
    {
        if(URotatingMovementComponent* RotatingMovement = Cast<URotatingMovementComponent>(AvatarActor->GetComponentByClass(URotatingMovementComponent::StaticClass())))
        {
            RotatingMovement->Deactivate();
        }
    }
}
