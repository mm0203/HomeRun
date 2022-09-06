// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidgetManager.h"
#include "RunGameStateBase.h"
#include "RunGameGameMode.h"

AGameWidgetManager::AGameWidgetManager()
{
    WidgetInstance = nullptr;

}
void AGameWidgetManager::BeginPlay()
{
    Super::BeginPlay();

    WidgetInstance = CreateWidget<UGameWidget>(GetWorld(), WidgetClass);

    if (WidgetInstance)
    {
        WidgetInstance->AddToViewport();
        WidgetInstance->UpdateScore(0);
        WidgetInstance->UpdateLife(3);
    }

    auto gameState = GetWorld()->GetGameState<ARunGameStateBase>();
    if (gameState)
    {
        gameState->ScoreUpdateDelegate.AddUObject(WidgetInstance, &UGameWidget::UpdateScore);
        gameState->LifeDelegate.AddUObject(WidgetInstance, &UGameWidget::UpdateLife);
    }

    auto GameMode = Cast<ARunGameGameMode>(GetWorld()->GetAuthGameMode());
    if(GameMode)
    {
        GameMode->GameStartDelegate.AddUObject(WidgetInstance, &UGameWidget::StartVisibility);
    }
}