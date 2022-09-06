// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelScript.generated.h"

class ARunGameGameMode;

UCLASS()
class RUNGAME_API ALevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ALevelScript();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void IsMove();

private:
	TArray<AActor*> FoundActors;
	FVector MoveSpeed;
	bool GameStart;
	ARunGameGameMode* GameMode;
};
