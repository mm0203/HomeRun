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
	GameOver = true;
	OpenLevel = "\0";
}

void ARunGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameState = GetWorld()->GetGameState<ARunGameStateBase>();

	// 3•bŒã‚ÉƒQ[ƒ€ŠJŽn
	FTimerHandle _TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &ARunGameGameMode::ToGameStart, 1.0f, false, 3.0f);

	UGameplayStatics::PlaySound2D(this, GameSound);
}

// Called every frame
void ARunGameGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GameState->GetLife() <= 0)
	{
		GameOver = true;
		FTimerHandle _TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &ARunGameGameMode::OpenLevelFunc, 1.0f, false, 2.0f);
	}
}

void ARunGameGameMode::OpenLevelFunc()
{
	UGameplayStatics::OpenLevel(GetWorld(), OpenLevel);
}

void ARunGameGameMode::ToGameStart()
{
	GameOver = false;
	GameStartDelegate.Broadcast();
}
