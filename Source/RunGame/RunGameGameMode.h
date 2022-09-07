// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sound/SoundCue.h"
#include "RunGameGameMode.generated.h"

// �f���Q�[�g�錾
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
	// �Q�[���J�n���ɌĂԊ֐�
	UFUNCTION(BlueprintCallable)
		void IsGameStart();
	// �Q�[���I�����ɌĂԊ֐�
	UFUNCTION(BlueprintCallable)
		void IsGameEnd();

	// �f���Q�[�g�Z�b�g�p�֐�
	void SetGameStartDelegate(FGameStartDelegate::FDelegate& Delegate)
	{
		GameStartDelegate.Add(Delegate);
	}
	void SetGameEndDelegate(FGameEndDelegate::FDelegate& Delegate)
	{
		GameEndDelegate.Add(Delegate);
	}

private:
	// �e��f���Q�[�g
	FGameStartDelegate GameStartDelegate;
	FGameEndDelegate GameEndDelegate;
};



