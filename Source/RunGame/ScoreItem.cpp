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
	// ‰¹
	//UGameplayStatics::PlaySound2D(this, ConsumptionSound);

	// ƒXƒRƒA‚ğ‰ÁZ
	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameState->ScoreAdd(Score);

	// íœ
	//Destroy();
}
