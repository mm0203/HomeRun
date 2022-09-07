// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameStateBase.h"

ARunGameStateBase::ARunGameStateBase()
{
	Score = 0;
	ItemNo = 0;
	PowerUp = false;
	Lane = 2;
	Life = 3;
	PowerUpTime = 3.0f;
}

void ARunGameStateBase::ScoreAdd(int score)
{
	// スコア加算
	Score += score;
	ScoreUpdateDelegate.Broadcast(Score);
}

void ARunGameStateBase::ItemBuff(int no)
{
	// アイテム取得
	ItemNo = no;
	ItemBuffDelegate.Broadcast(ItemNo);
}

void ARunGameStateBase::LifeCalc(int life)
{
	// ライフ加減
	Life -= life;
	LifeDelegate.Broadcast(Life);
}

void ARunGameStateBase::IsPowerUp()
{
	PowerUp = true;
	PowerUpDelegate.Broadcast();

	// ラムダ
	TFunction<void(void)> PowerUpLift = [this]() {PowerUp = false; };

	// 3秒後にパワーアップ解除
	FTimerHandle TimerHandle;
	FTimerManager& TimerManager = GetWorldTimerManager();
	TimerManager.SetTimer(TimerHandle, (TFunction<void(void)>&&)PowerUpLift, 1.0f, false, PowerUpTime);
}

