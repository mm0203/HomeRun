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

	// 3�b��ɃQ�[���J�n
	FTimerHandle _TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &ARunGameGameMode::IsGameStart, 1.0f, false, 3.0f);

	UGameplayStatics::PlaySound2D(this, GameSound);
}

void ARunGameGameMode::IsGameStart()
{
	// �Q�[���J�n
	GamePlay = true;
	// �Q�[���J�n���̃f���Q�[�g�Ăяo��
	GameStartDelegate.Broadcast();
}

void ARunGameGameMode::IsGameEnd()
{
	GamePlay = false;

	// �ړ��t��
	MoveSpeed = FVector(0, 0, 0);

	// �Q�[���I�����̃f���Q�[�g�Ăяo��
	GameEndDelegate.Broadcast();

	// �����_
	TFunction<void(void)> OpenLevelFunc = [this]() {UGameplayStatics::OpenLevel(GetWorld(), OpenLevel); };

	// �Q�b��ɃV�[���J��
	FTimerHandle _TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_TimerHandle, (TFunction<void(void)>&&)OpenLevelFunc, 1.0f, false, 2.0f);
}

