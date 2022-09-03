// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameStateBase.h"
#include "RunGameGameMode.generated.h"

UCLASS(minimalapi)
class ARunGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARunGameGameMode();

	DECLARE_MULTICAST_DELEGATE(FGameOverDelegate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool GameOver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName OpenLevel;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FGameOverDelegate LifeDelegate;

	ARunGameStateBase* GameState;
};



