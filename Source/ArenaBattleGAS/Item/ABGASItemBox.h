// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayCueInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "ABGASItemBox.generated.h"

class UBoxComponent;

UCLASS()
class ARENABATTLEGAS_API AABGASItemBox : public AActor, public IAbilitySystemInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetAbilitySystem, Category = "Component")
    TObjectPtr<UAbilitySystemComponent> AbilitySystem;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTrigger, Category = "Component")
    TObjectPtr<UBoxComponent> Trigger;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> Mesh;

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<UGameplayEffect> GameplayEffectClass;

    UPROPERTY(EditAnywhere, Category = "Config")
    FGameplayCueTag GameplayCueTag;

public:
    AABGASItemBox();

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
    virtual void PostInitializeComponents() override;

    void ApplyEffectToTarget(AActor* Target);
    void InvokeGameplayCue(AActor* Target);

protected:
    UFUNCTION(BlueprintGetter)
    UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }

    UFUNCTION(BlueprintGetter)
    UBoxComponent* GetTrigger() const { return Trigger; }

    UFUNCTION(BlueprintGetter)
    UStaticMeshComponent* GetMesh() const { return Mesh; }

public:
    /* AbilitySystemInterface */
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };
};
