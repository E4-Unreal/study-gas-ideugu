// Fill out your copyright notice in the Description page of Project Settings.

#include "ABTA_SphereMultiTrace.h"

#include "AbilitySystemGlobals.h"
#include "GameFramework/Character.h"
#include "Physics/ABCollision.h"

FGameplayAbilityTargetDataHandle AABTA_SphereMultiTrace::MakeTargetData() const
{
    // 충돌 검사
    ACharacter* Character = CastChecked<ACharacter>(SourceActor);

    UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(SourceActor);
    if(!AbilitySystem) return FGameplayAbilityTargetDataHandle();

    TArray<FOverlapResult> OverlapResults;
    const float SkillRadius = 800.f;

    FVector Origin = Character->GetActorLocation();
    FCollisionQueryParams Params(SCENE_QUERY_STAT(AABTA_SphereMultiTrace), false, Character);
    GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeSphere(SkillRadius), Params);

    TArray<TWeakObjectPtr<AActor>> HitActors;
    for(const FOverlapResult& OverlapResult : OverlapResults)
    {
        AActor* HitActor = OverlapResult.OverlapObjectHandle.FetchActor<AActor>();
        if(HitActor && !HitActors.Contains(HitActor))
        {
            HitActors.Add(HitActor);
        }
    }

    FGameplayAbilityTargetData_ActorArray* ActorsData = new FGameplayAbilityTargetData_ActorArray();
    ActorsData->SetActors(HitActors);

#if ENABLE_DRAW_DEBUG
    FColor DrawColor = HitActors.Num() > 0 ? FColor::Green : FColor::Red;
    DrawDebugSphere(GetWorld(), Origin, SkillRadius, 16, DrawColor, false, 5.f);
#endif

    return FGameplayAbilityTargetDataHandle(ActorsData);
}
