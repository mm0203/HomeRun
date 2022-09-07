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
    UTextBlock* StartTextBlock;
    UTextBlock* EndTextBlock;


public:
    UGameWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeOnInitialized() override;

public:
    // UI�X�V�֐�
    UFUNCTION()
    void UpdateLife(int life);

    // �X�R�A�X�V�֐�
    UFUNCTION()
    void UpdateScore(int score);
    
    // �X�^�[�g����UI�\���֐�
    UFUNCTION()
    void StartVisibility();

    // �Q�[���I������UI�\���֐�
    UFUNCTION()
    void EndVisibility();
};
