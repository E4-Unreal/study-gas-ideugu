// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASItemBox.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Components/BoxComponent.h"
#include "Physics/ABCollision.h"

AABGASItemBox::AABGASItemBox()
{
    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

    RootComponent = Trigger;
    Mesh->SetupAttachment(Trigger);

    Trigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
    Trigger->SetBoxExtent(FVector(40.f, 42.f, 30.f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
    if(BoxMeshRef.Object)
    {
        Mesh->SetStaticMesh(BoxMeshRef.Object);
    }
    Mesh->SetRelativeLocation(FVector(0.f, -3.5f, -30.f));
    Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void AABGASItemBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    InvokeGameplayCue(OtherActor);
    ApplyEffectToTarget(OtherActor);

    Mesh->SetHiddenInGame(true);
    SetActorEnableCollision(false);
    SetLifeSpan(2.f);
}

void AABGASItemBox::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    AbilitySystem->InitAbilityActorInfo(this, this);
}

void AABGASItemBox::ApplyEffectToTarget(AActor* Target)
{
    if(UAbilitySystemComponent* TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target))
    {
        if(GameplayEffectClass)
        {
            FGameplayEffectContextHandle EffectContextHandle = AbilitySystem->MakeEffectContext();
            FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContextHandle);
            AbilitySystem->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetSystem);
        }
    }
}

void AABGASItemBox::InvokeGameplayCue(AActor* Target)
{
    FGameplayCueParameters CueParameters;
    CueParameters.SourceObject = this;
    CueParameters.Instigator = Target;
    CueParameters.Location = GetActorLocation();

    AbilitySystem->ExecuteGameplayCue(GameplayCueTag.GameplayCueTag, CueParameters);
}
