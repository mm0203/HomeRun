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
	// スタートボタン
	UButton* StartButton;

    // 終了ボタン
    UButton* ExitButton;


    UTitleWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeOnInitialized() override;

public:
    // スタートクリック呼び出し
    UFUNCTION(BlueprintCallable, Category = "TitleWidget")
        void OnStartClicked();

    // 終了クリック呼び出し
    UFUNCTION(BlueprintCallable, Category = "TitleWidget")
        void OnExitClicked();
};
