// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "TitleWidget.generated.h"

UCLASS()
class RUNGAME_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// �X�^�[�g�{�^��
	UButton* StartButton;

    // �I���{�^��
    UButton* ExitButton;


    UTitleWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeOnInitialized() override;

public:
    // �X�^�[�g�N���b�N�Ăяo��
    UFUNCTION(BlueprintCallable, Category = "TitleWidget")
        void OnStartClicked();

    // �I���N���b�N�Ăяo��
    UFUNCTION(BlueprintCallable, Category = "TitleWidget")
        void OnExitClicked();
};
