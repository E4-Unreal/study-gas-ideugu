// Fill out your copyright notice in the Description page of Project Settings.

#include "ABTA_Trace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbility.h"
#include "Attribute/ABGASCharacterAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Physics/ABCollision.h"

AABTA_Trace::AABTA_Trace()
{

}

void AABTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
    Super::StartTargeting(Ability);

    SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void AABTA_Trace::ConfirmTargetingAndContinue()
{
    if(SourceActor)
    {
        FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
        TargetDataReadyDelegate.Broadcast(DataHandle);
    }
}

FGameplayAbilityTargetDataHandle AABTA_Trace::MakeTargetData() const
{
    // AttackRange 값 가져오기
    bool bFoundAttackRange;
    const float AttackRange = UAbilitySystemBlueprintLibrary::GetFloatAttribute(SourceActor, UABGASCharacterAttributeSet::GetAttackRangeAttribute(), bFoundAttackRange);

    // AttackRadius 값 가져오기
    bool bFoundAttackRadius;
    const float AttackRadius = UAbilitySystemBlueprintLibrary::GetFloatAttribute(SourceActor, UABGASCharacterAttributeSet::GetAttackRadiusAttribute(), bFoundAttackRadius);

    // 유효성 검사
    if(!(bFoundAttackRange && bFoundAttackRadius)) return FGameplayAbilityTargetDataHandle();

    // 충돌 검사
    ACharacter* Character = CastChecked<ACharacter>(SourceActor);

    FHitResult OutHitResult;
    FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(UABTA_Trace), false, Character);
    const FVector Forward = Character->GetActorForwardVector();
    const FVector Start = Character->GetActorLocation() + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
    const FVector End = Start + Forward * AttackRange;

    bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeSphere(AttackRadius), CollisionQueryParams);
    FGameplayAbilityTargetDataHandle DataHandle;
    if(HitDetected)
    {
        FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(OutHitResult);
        DataHandle.Add(TargetData);
    }

#if ENABLE_DRAW_DEBUG
    FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
    float CapsuleHalfHeight = AttackRange * 0.5f;
    FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
    DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor, false, 5.f);
#endif

    return DataHandle;
}
