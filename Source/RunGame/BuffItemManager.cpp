// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffItemManager.h"
#include "RunGameStateBase.h"

// Sets default values
ABuffItemManager::ABuffItemManager()
{
}

void ABuffItemManager::BeginPlay()
{
	Super::BeginPlay();

	// デリゲート登録
	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	if (GameState)
	{
		FItemBuffDelegate::FDelegate ItemBuffDelegate;
		ItemBuffDelegate.BindDynamic(this, &ABuffItemManager::BuffEffect);
		GameState->SetItemBuffDelegate(ItemBuffDelegate);
	}
}

void ABuffItemManager::BuffEffect(int no)
{
	// パワーアップ
	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameState->IsPowerUp();
}


