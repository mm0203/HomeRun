// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameStateBase.h"
#include "Kismet/KismetStringLibrary.h"

ARunGameStateBase::ARunGameStateBase()
{
	Score = 0;
	ItemNo = 0;
}

void ARunGameStateBase::ScoreAdd(int score)
{
	// スコア加算
	Score += score;

	// 加算されたスコアを渡す
	ScoreUpdateDelegate.Broadcast(Score);
	FString cnt = UKismetStringLibrary::Conv_IntToString(Score);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, cnt);

}

void ARunGameStateBase::ItemBuff(int no)
{
	ItemNo = no;
	ItemBuffDelegate.Broadcast(ItemNo);
	FString cnt = UKismetStringLibrary::Conv_IntToString(ItemNo);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, cnt);
}
