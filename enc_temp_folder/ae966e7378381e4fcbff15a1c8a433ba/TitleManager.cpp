// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleManager.h"

ATitleManager::ATitleManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATitleManager::BeginPlay()
{
	Super::BeginPlay();

    WidgetInstance = CreateWidget<UTitleWidget>(GetWorld(), WidgetClass);

    if (WidgetInstance)
    {
        WidgetInstance->AddToViewport();
    }

    //WidgetInstance->StartButton->OnClicked.AddDynamic(this, &ATitleManager::OnStartClicked);
}

void ATitleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATitleManager::OnStartClicked()
{
    WidgetInstance->OnStartClicked();
}