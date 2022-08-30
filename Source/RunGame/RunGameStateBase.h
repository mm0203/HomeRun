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

	// マルチキャストを宣言、１つ引数を使えるように_OneParamをつける
	DECLARE_MULTICAST_DELEGATE_OneParam(FScoreUpdateDelegate, int);

	// スコア加算関数
	void ScoreAdd(int score);

	// デリゲートを作成
	FScoreUpdateDelegate ScoreUpdateDelegate;

protected:
	int Score;
private:


};
