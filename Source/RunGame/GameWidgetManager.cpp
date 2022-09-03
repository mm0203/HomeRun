// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidgetManager.h"
#include "RunGameStateBase.h"

// Sets default values
AGameWidgetManager::AGameWidgetManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    WidgetInstance = nullptr;

}

// Called when the game starts or when spawned
void AGameWidgetManager::BeginPlay()
{
    Super::BeginPlay();

    WidgetInstance = CreateWidget<UGameWidget>(GetWorld(), WidgetClass);

    if (WidgetInstance)
    {
        WidgetInstance->AddToViewport();
        WidgetInstance->UpdateScore(0);
        WidgetInstance->UpdateLife(3);
    }

    auto gameState = GetWorld()->GetGameState<ARunGameStateBase>();
    if (gameState != nullptr)
    {
        gameState->ScoreUpdateDelegate.AddUObject(WidgetInstance, &UGameWidget::UpdateScore);
        gameState->LifeDelegate.AddUObject(WidgetInstance, &UGameWidget::UpdateLife);
    }
}

// Called every frame
void AGameWidgetManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}