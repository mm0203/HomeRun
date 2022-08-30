// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API UScoreItemWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
    // テキスト保存用
    UTextBlock* TextBlock;

public:
    UScoreItemWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeOnInitialized() override;

public:
    // スコア更新関数
    void UpdateScore(int score);
};
