// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreItem.h"
#include "RunGameStateBase.h"

AScoreItem::AScoreItem()
{
	Score = 0;

	Tags.Add(FName("ScoreItem"));
}

void AScoreItem::ToCatchItem()
{
	// ��
	//UGameplayStatics::PlaySound2D(this, ConsumptionSound);

	// �X�R�A�����Z
	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameState->ScoreAdd(Score);

	// �폜
	//Destroy();
}
