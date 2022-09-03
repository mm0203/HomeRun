// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    // テキスト保存用
    UTextBlock* ScoreTextBlock;
    UTextBlock* LifeTextBlock;

public:
    UGameWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeOnInitialized() override;

public:
    // UI更新関数
    void UpdateLife(int life);
    void UpdateScore(int score);
};
