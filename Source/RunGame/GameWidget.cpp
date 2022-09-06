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
    // ������
    Super::NativeOnInitialized();

    // �e�L�X�g���擾
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
    // �e�L�X�g + �X�R�A�\��
    FString str = FString::FromInt(score);

    if (LifeTextBlock)
    {
        // �e�L�X�g��ݒ�
        LifeTextBlock->SetText(FText::FromString(str));
    }
}

void UGameWidget::UpdateScore(int score)
{
    // �e�L�X�g + �X�R�A�\��
    FString str = FString::FromInt(score);

    if (ScoreTextBlock)
    {
        // �e�L�X�g��ݒ�
        ScoreTextBlock->SetText(FText::FromString(str));
    }
}

void UGameWidget::StartVisibility()
{
    StartTextBlock->SetVisibility(ESlateVisibility::Hidden);
    StartTextBlock = nullptr;
}
