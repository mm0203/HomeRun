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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool GameOver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName OpenLevel;

	UPROPERTY(EditAnywhere)
		USoundCue* GameSound;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FGameStartDelegate GameStartDelegate;

	ARunGameStateBase* GameState;

	UFUNCTION()
		void OpenLevelFunc();

	UFUNCTION(BlueprintCallable)
		void ToGameStart();
};



