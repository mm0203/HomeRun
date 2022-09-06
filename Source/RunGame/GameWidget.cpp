// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

UGameWidget::UGameWidget(const FObjectInitializer& ObjectInitializer)
    : UUserWidget(ObjectInitializer)
{
    ScoreTextBlock = nullptr;
    LifeTextBlock = nullptr;
}

void UGameWidget::NativeOnInitialized()
{
    // 初期化
    Super::NativeOnInitialized();

    // テキストを取得
    UTextBlock* pTextBlock = Cast<UTextBlock>(GetWidgetFromName("ScoreText"));
    if (pTextBlock)
    {
        ScoreTextBlock = pTextBlock;
    }

    pTextBlock = Cast<UTextBlock>(GetWidgetFromName("LifeText"));
    if (pTextBlock)
    {
        LifeTextBlock = pTextBlock;
    }

    pTextBlock = Cast<UTextBlock>(GetWidgetFromName("StartText"));
    if (pTextBlock)
    {
        StartTextBlock = pTextBlock;
    }
}

void UGameWidget::UpdateLife(int score)
{
    // テキスト + スコア表示
    FString str = FString::FromInt(score);

    if (LifeTextBlock)
    {
        // テキストを設定
        LifeTextBlock->SetText(FText::FromString(str));
    }
}

void UGameWidget::UpdateScore(int score)
{
    // テキスト + スコア表示
    FString str = FString::FromInt(score);

    if (ScoreTextBlock)
    {
        // テキストを設定
        ScoreTextBlock->SetText(FText::FromString(str));
    }
}

void UGameWidget::StartVisibility()
{
    StartTextBlock->SetVisibility(ESlateVisibility::Hidden);
    StartTextBlock = nullptr;
}
