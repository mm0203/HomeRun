// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sound/SoundCue.h"
#include "RunGameGameMode.generated.h"

// デリゲート宣言
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameEndDelegate);

UCLASS(minimalapi)
class ARunGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARunGameGameMode();

	UPROPERTY(EditAnywhere)
		bool GamePlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName OpenLevel;

	UPROPERTY(EditAnywhere)
		USoundCue* GameSound;
protected:
	virtual void BeginPlay() override;

public:
	// ゲーム開始時に呼ぶ関数
	UFUNCTION(BlueprintCallable)
		void IsGameStart();
	// ゲーム終了時に呼ぶ関数
	UFUNCTION(BlueprintCallable)
		void IsGameEnd();

	// デリゲートセット用関数
	void SetGameStartDelegate(FGameStartDelegate::FDelegate& Delegate)
	{
		GameStartDelegate.Add(Delegate);
	}
	void SetGameEndDelegate(FGameEndDelegate::FDelegate& Delegate)
	{
		GameEndDelegate.Add(Delegate);
	}

private:
	// 各種デリゲート
	FGameStartDelegate GameStartDelegate;
	FGameEndDelegate GameEndDelegate;
};



