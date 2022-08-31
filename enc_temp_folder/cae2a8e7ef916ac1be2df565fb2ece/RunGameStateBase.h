// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RunGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API ARunGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	ARunGameStateBase();

	// �}���`�L���X�g�f���Q�[�g
	DECLARE_MULTICAST_DELEGATE_OneParam(FScoreUpdateDelegate, int);
	DECLARE_MULTICAST_DELEGATE_OneParam(FItemBuffDelegate, int);

	// �X�R�A���Z�֐�
	void ScoreAdd(int score);
	// �A�C�e���o�t�֐�
	void ItemBuff(int no);

	// �f���Q�[�g�쐬
	FScoreUpdateDelegate ScoreUpdateDelegate;
	FItemBuffDelegate ItemBuffDelegate;

protected:
	int Score;
	int ItemNo;

private:


};
