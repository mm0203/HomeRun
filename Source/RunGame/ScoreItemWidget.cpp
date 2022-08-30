// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreItemWidget.h"

UScoreItemWidget::UScoreItemWidget(const FObjectInitializer& ObjectInitializer)
    : UUserWidget(ObjectInitializer)
{
    TextBlock = nullptr;
}

void UScoreItemWidget::NativeOnInitialized()
{
    // 初期化
    Super::NativeOnInitialized();

    // テキストを取得
    UTextBlock* pTextBlock = Cast<UTextBlock>(GetWidgetFromName("ScoreText"));
    ensure(pTextBlock != nullptr);
    TextBlock = pTextBlock;
}

void UScoreItemWidget::UpdateScore(int score)
{
    // テキスト + スコア表示
    FString str = TEXT("Score:") + FString::FromInt(score);

    ensure(TextBlock != nullptr);
    if (TextBlock)
    {
        // テキストを設定
        TextBlock->SetText(FText::FromString(str));
    }
}