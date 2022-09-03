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
}

// Called every frame
void ARunGameGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GameState->GetLife() <= 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), OpenLevel);
	}
}