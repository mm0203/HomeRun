// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreItem.h"
#include "RunGameStateBase.h"

AScoreItem::AScoreItem()
{
	Score = 0;

	Tags.Add(FName("ScoreItem"));
}

void AScoreItem::ToCatchItem()
{
	// 音
	//UGameplayStatics::PlaySound2D(this, ConsumptionSound);

	// スコアを加算
	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameState->ScoreAdd(Score);

	// 削除
	//Destroy();
}
