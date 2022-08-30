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

	// �}���`�L���X�g��錾�A�P�������g����悤��_OneParam������
	DECLARE_MULTICAST_DELEGATE_OneParam(FScoreUpdateDelegate, int);

	// �X�R�A���Z�֐�
	void ScoreAdd(int score);

	// �f���Q�[�g���쐬
	FScoreUpdateDelegate ScoreUpdateDelegate;

protected:
	int Score;
private:


};
