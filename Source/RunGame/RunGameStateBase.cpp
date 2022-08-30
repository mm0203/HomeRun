// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameStateBase.h"
#include "Kismet/KismetStringLibrary.h"

ARunGameStateBase::ARunGameStateBase()
{
	Score = 0;
}

void ARunGameStateBase::ScoreAdd(int score)
{
	// ƒXƒRƒA‰ÁŽZ
	Score += score;

	// ‰ÁŽZ‚³‚ê‚½ƒXƒRƒA‚ð“n‚·
	ScoreUpdateDelegate.Broadcast(Score);
	FString cnt = UKismetStringLibrary::Conv_IntToString(Score);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, cnt);

}