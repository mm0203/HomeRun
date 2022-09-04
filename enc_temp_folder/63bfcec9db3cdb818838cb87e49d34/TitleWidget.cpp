// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

UTitleWidget::UTitleWidget(const FObjectInitializer& ObjectInitializer)
    : UUserWidget(ObjectInitializer)
{
}

void UTitleWidget::NativeOnInitialized()
{
    // 初期化
    Super::NativeOnInitialized();

    // スタートボタン
    UButton* pButton = Cast<UButton>(GetWidgetFromName("StartBtn"));
    if (pButton)
    {
        StartButton = pButton;
        StartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnStartClicked);
    }

    // 終了ボタン
    if (pButton)
    {
        pButton = Cast<UButton>(GetWidgetFromName("ExitBtn"));
        ExitButton = pButton;
        ExitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnExitClicked);
    }
}

void UTitleWidget::OnStartClicked()
{
    if (StartButton)
    {
        if (StartButton->OnClicked.IsBound())
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Click");
            FTimerHandle _TimerHandle;
            //GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &UTitleWidget::OpenLevelFunc, 1.0f, false, 1.0f);
        }
    }
}

void UTitleWidget::OnExitClicked()
{
    if (ExitButton)
    {
        if (ExitButton->OnClicked.IsBound())
        {
            FTimerHandle _TimerHandle;
            //GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &UTitleWidget::QuitGame, 1.0f, false, 1.0f);
        }
    }
}