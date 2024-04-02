// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASFountain.h"

#include "GameFramework/RotatingMovementComponent.h"

AABGASFountain::AABGASFountain()
{
    RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
    ActionPeriod = 3.f;
}

void AABGASFountain::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    RotatingMovement->bAutoActivate = false;
    RotatingMovement->Deactivate();
}

void AABGASFountain::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(ActionTimer, this, &ThisClass::TimerAction, ActionPeriod, true, 0.f);
}

void AABGASFountain::TimerAction()
{
    if(!RotatingMovement->IsActive())
        RotatingMovement->Activate(true);
    else
        RotatingMovement->Deactivate();
}
