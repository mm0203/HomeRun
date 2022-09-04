// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffItemManager.h"
#include "RunGameStateBase.h"

// Sets default values
ABuffItemManager::ABuffItemManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABuffItemManager::BeginPlay()
{
	Super::BeginPlay();
	auto gameState = GetWorld()->GetGameState<ARunGameStateBase>();
	if (gameState != nullptr)
	{
		gameState->ItemBuffDelegate.AddUObject(this, &ABuffItemManager::BuffEffect);
	}
}

// Called every frame
void ABuffItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuffItemManager::BuffEffect(int no)
{
	// パワーアップ
	auto gameState = GetWorld()->GetGameState<ARunGameStateBase>();
	gameState->SetPowerUp(true);

	// 3秒後にバフ効果削除
	FTimerHandle TimerHandle;
	FTimerManager& TimerManager = GetWorldTimerManager();
	TimerManager.SetTimer(TimerHandle, this, &ABuffItemManager::PowerUpLift, 1.0f, false, 3.0f);
}

void ABuffItemManager::PowerUpLift()
{
	// バフ効果消える
	auto gameState = GetWorld()->GetGameState<ARunGameStateBase>();
	gameState->SetPowerUp(false);
}


