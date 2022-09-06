// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameStateBase.h"
#include "Sound/SoundCue.h"
#include "RunGameGameMode.generated.h"

UCLASS(minimalapi)
class ARunGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARunGameGameMode();

	DECLARE_MULTICAST_DELEGATE(FGameStartDelegate);
	DECLARE_MULTICAST_DELEGATE(FGameEndDelegate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool GameStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool GameEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName OpenLevel;

	UPROPERTY(EditAnywhere)
		USoundCue* GameSound;
protected:
	virtual void BeginPlay() override;

public:
	// ゲーム開始・終了デリゲート
	FGameStartDelegate GameStartDelegate;
	FGameEndDelegate GameEndDelegate;

	ARunGameStateBase* GameState;

	// シーン遷移関数
	UFUNCTION()
		void OpenLevelFunc();
	// ゲーム開始時に呼ぶ関数
	UFUNCTION(BlueprintCallable)
		void IsGameStart();
	// ゲーム終了時に呼ぶ関数
	UFUNCTION(BlueprintCallable)
		void IsGameEnd();
};



