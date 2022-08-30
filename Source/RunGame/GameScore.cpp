// Fill out your copyright notice in the Description page of Project Settings.


#include "GameScore.h"

UGameScore::UGameScore(const FObjectInitializer& ObjectInitializer)
    : UUserWidget(ObjectInitializer)
{
    TextBlock = nullptr;
}

void UGameScore::NativeOnInitialized()
{
    // 初期化
    Super::NativeOnInitialized();

    // テキストを取得
    UTextBlock* pTextBlock = Cast<UTextBlock>(GetWidgetFromName("ScoreText"));
    ensure(pTextBlock != nullptr);
    TextBlock = pTextBlock;
}

void UGameScore::UpdateScore(int score)
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