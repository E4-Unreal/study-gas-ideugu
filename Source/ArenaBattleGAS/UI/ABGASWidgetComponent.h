// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ABGASWidgetComponent.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class ARENABATTLEGAS_API UABGASWidgetComponent : public UWidgetComponent
{
    GENERATED_BODY()

public:
    UABGASWidgetComponent();

protected:
    virtual void InitWidget() override;
};
