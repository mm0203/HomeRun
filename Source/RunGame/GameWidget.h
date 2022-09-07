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
    UTextBlock* StartTextBlock;
    UTextBlock* EndTextBlock;


public:
    UGameWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeOnInitialized() override;

public:
    // UI更新関数
    UFUNCTION()
    void UpdateLife(int life);

    // スコア更新関数
    UFUNCTION()
    void UpdateScore(int score);
    
    // スタート時のUI表示関数
    UFUNCTION()
    void StartVisibility();

    // ゲーム終了時のUI表示関数
    UFUNCTION()
    void EndVisibility();
};
