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
    // �e�L�X�g�ۑ��p
    UTextBlock* ScoreTextBlock;
    UTextBlock* LifeTextBlock;

public:
    UGameWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeOnInitialized() override;

public:
    // UI�X�V�֐�
    void UpdateLife(int life);
    void UpdateScore(int score);
};
