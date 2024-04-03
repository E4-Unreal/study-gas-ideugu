// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASWidgetComponent.h"

#include "ABGASUserWidget.h"

UABGASWidgetComponent::UABGASWidgetComponent()
{

}

void UABGASWidgetComponent::InitWidget()
{
    Super::InitWidget();

    if(UABGASUserWidget* ABGASUserWidget = Cast<UABGASUserWidget>(GetWidget()))
    {
        ABGASUserWidget->SetOwner(GetOwner());
    }
}
