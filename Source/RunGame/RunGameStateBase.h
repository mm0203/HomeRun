// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RunGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API ARunGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	ARunGameStateBase();

	// マルチキャストデリゲート
	DECLARE_MULTICAST_DELEGATE_OneParam(FScoreUpdateDelegate, int);
	DECLARE_MULTICAST_DELEGATE_OneParam(FItemBuffDelegate, int);

	// スコア加算関数
	void ScoreAdd(int score);
	// アイテムバフ関数
	void ItemBuff(int no);

	// デリゲート作成
	FScoreUpdateDelegate ScoreUpdateDelegate;
	FItemBuffDelegate ItemBuffDelegate;

protected:
	int Score;
	int ItemNo;

private:


};
