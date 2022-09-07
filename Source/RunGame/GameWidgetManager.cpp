// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidgetManager.h"
#include "RunGameStateBase.h"
#include "RunGameGameMode.h"
#include "AI/NavigationSystemBase.h"

AGameWidgetManager::AGameWidgetManager()
{
    WidgetInstance = nullptr;

}
void AGameWidgetManager::BeginPlay()
{
    Super::BeginPlay();

    WidgetInstance = CreateWidget<UGameWidget>(GetWorld(), WidgetClass);

    auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
    auto GameMode = Cast<ARunGameGameMode>(GetWorld()->GetAuthGameMode());

    if (WidgetInstance)
    {
        WidgetInstance->AddToViewport();
        WidgetInstance->UpdateScore(0);
        WidgetInstance->UpdateLife(GameState->GetLife());
    }

    // デリゲート登録
    if (GameState)
    {
        // スコア
        FScoreUpdateDelegate::FDelegate ScoreUpdateDelegate;
        ScoreUpdateDelegate.BindDynamic(WidgetInstance, &UGameWidget::UpdateScore);
        GameState->SetGameStartDelegate(ScoreUpdateDelegate);

        // ライフ
        FLifeDelegate::FDelegate LifeDelegate;
        LifeDelegate.BindDynamic(WidgetInstance, &UGameWidget::UpdateLife);
        GameState->SetLifeDelegate(LifeDelegate);
    }

    if(GameMode)
    {
        // スタート
        FGameStartDelegate::FDelegate GameStartDelegate;
        GameStartDelegate.BindDynamic(WidgetInstance, &UGameWidget::StartVisibility);
        GameMode->SetGameStartDelegate(GameStartDelegate);

        // 終了
        FGameStartDelegate::FDelegate GameEndDelegate;
        GameEndDelegate.BindDynamic(WidgetInstance, &UGameWidget::EndVisibility);
        GameMode->SetGameEndDelegate(GameEndDelegate);
    }
}