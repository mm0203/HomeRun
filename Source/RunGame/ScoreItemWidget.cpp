// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreItemWidget.h"

UScoreItemWidget::UScoreItemWidget(const FObjectInitializer& ObjectInitializer)
    : UUserWidget(ObjectInitializer)
{
    TextBlock = nullptr;
}

void UScoreItemWidget::NativeOnInitialized()
{
    // ������
    Super::NativeOnInitialized();

    // �e�L�X�g���擾
    UTextBlock* pTextBlock = Cast<UTextBlock>(GetWidgetFromName("ScoreText"));
    ensure(pTextBlock != nullptr);
    TextBlock = pTextBlock;
}

void UScoreItemWidget::UpdateScore(int score)
{
    // �e�L�X�g + �X�R�A�\��
    FString str = TEXT("Score:") + FString::FromInt(score);

    ensure(TextBlock != nullptr);
    if (TextBlock)
    {
        // �e�L�X�g��ݒ�
        TextBlock->SetText(FText::FromString(str));
    }
}