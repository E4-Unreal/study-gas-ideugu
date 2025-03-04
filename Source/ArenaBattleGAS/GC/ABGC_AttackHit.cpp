﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGC_AttackHit.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

UABGC_AttackHit::UABGC_AttackHit()
{
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionRef(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
    if(ExplosionRef.Object)
    {
        ParticleSystem = ExplosionRef.Object;
    }
}

bool UABGC_AttackHit::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
    if(const FHitResult* HitResult = Parameters.EffectContext.GetHitResult())
    {
        UGameplayStatics::SpawnEmitterAtLocation(MyTarget, ParticleSystem, HitResult->ImpactPoint, FRotator::ZeroRotator, true);
    }
    else
    {
        for(const auto& HitActor : Parameters.EffectContext.Get()->GetActors())
        {
            if(HitActor.IsValid())
            {
                UGameplayStatics::SpawnEmitterAtLocation(MyTarget, ParticleSystem, HitActor->GetActorLocation(), FRotator::ZeroRotator, true);
            }
        }
    }

    return Super::OnExecute_Implementation(MyTarget, Parameters);
}
