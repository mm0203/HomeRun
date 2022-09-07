// Copyright Epic Games, Inc. All Rights Reserved.

#include "RunGameGameMode.h"
#include "RunGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ARunGameGameMode::ARunGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	MoveSpeed = FVector(0, 0, 0);
	GamePlay = false;
	OpenLevel = "\0";
}

void ARunGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameState = GetWorld()->GetGameState<ARunGameStateBase>();

	// 3秒後にゲーム開始
	FTimerHandle _TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &ARunGameGameMode::IsGameStart, 1.0f, false, 3.0f);

	UGameplayStatics::PlaySound2D(this, GameSound);
}

void ARunGameGameMode::IsGameStart()
{
	// ゲーム開始
	GamePlay = true;
	// ゲーム開始時のデリゲート呼び出し
	GameStartDelegate.Broadcast();
}

void ARunGameGameMode::IsGameEnd()
{
	GamePlay = false;

	// 移動付加
	MoveSpeed = FVector(0, 0, 0);

	// ゲーム終了時のデリゲート呼び出し
	GameEndDelegate.Broadcast();

	// ２秒後にシーン遷移
	FTimerHandle _TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &ARunGameGameMode::OpenLevelFunc, 1.0f, false, 2.0f);
}

void ARunGameGameMode::OpenLevelFunc()
{
	UGameplayStatics::OpenLevel(GetWorld(), OpenLevel);
}

