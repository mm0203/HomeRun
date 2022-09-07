// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RunGameStateBase.generated.h"

// �f���Q�[�g�錾
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreUpdateDelegate, int, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemBuffDelegate, int, No);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLifeDelegate, int, Life);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPowerUpDelegate);

UCLASS()
class RUNGAME_API ARunGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	ARunGameStateBase();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "GameState")
		int Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "GameState")
		bool PowerUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "GameState")
		float PowerUpTime;

	// �X�R�A���Z�֐�
	void ScoreAdd(int score);
	// �A�C�e���o�t�֐�
	void ItemBuff(int no);
	// ���C�t�����֐�
	void LifeCalc(int life);
	// �p���[�A�b�v�֐�
	void IsPowerUp();

protected:
	int Score;
	int ItemNo;
	int Lane;

public:
	// �f���Q�[�g�Z�b�g�p�֐�
	void SetGameStartDelegate(FScoreUpdateDelegate::FDelegate& Delegate)
	{
		ScoreUpdateDelegate.Add(Delegate);
	}
	void SetItemBuffDelegate(FItemBuffDelegate::FDelegate& Delegate)
	{
		ItemBuffDelegate.Add(Delegate);
	}
	void SetLifeDelegate(FLifeDelegate::FDelegate& Delegate)
	{
		LifeDelegate.Add(Delegate);
	}
	void SetPowerUpDelegate(FPowerUpDelegate::FDelegate& Delegate)
	{
		PowerUpDelegate.Add(Delegate);
	}

	UFUNCTION(BlueprintCallable)
	bool& GetPowerUp() { return PowerUp; }
	void SetPowerUp(bool value) { PowerUp = value; }

	int& GetLane() { return Lane; }
	void SetLane(int value) { Lane = value; }

	UFUNCTION(BlueprintCallable)
	int& GetLife() { return Life; }
	void SetLife(int value) { Life = value; }

private:
	// �e��f���Q�[�g
	FScoreUpdateDelegate ScoreUpdateDelegate;
	FItemBuffDelegate ItemBuffDelegate;
	FLifeDelegate LifeDelegate;
	FPowerUpDelegate PowerUpDelegate;
};
