// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleManager.h"

ATitleManager::ATitleManager()
{
}

void ATitleManager::BeginPlay()
{
	Super::BeginPlay();

    WidgetInstance = CreateWidget<UTitleWidget>(GetWorld(), WidgetClass);

    if (WidgetInstance)
    {
        WidgetInstance->AddToViewport();

        // ƒNƒŠƒbƒNŽž‚ÌƒfƒŠƒQ[ƒg“o˜^
        WidgetInstance->StartButton->OnClicked.AddDynamic(WidgetInstance, &UTitleWidget::OnStartClicked);
        WidgetInstance->ExitButton->OnClicked.AddDynamic(WidgetInstance, &UTitleWidget::OnExitClicked);
    }
}

void ATitleManager::OnStartClicked()
{
    WidgetInstance->OnStartClicked();
}