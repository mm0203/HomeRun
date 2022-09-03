// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameStateBase.h"

ARunGameStateBase::ARunGameStateBase()
{
	Score = 0;
	ItemNo = 0;
	PowerUp = false;
	Lane = 2;
	Life = 3;
}

void ARunGameStateBase::ScoreAdd(int score)
{
	// �X�R�A���Z
	Score += score;
	ScoreUpdateDelegate.Broadcast(Score);
}

void ARunGameStateBase::ItemBuff(int no)
{
	// �A�C�e���擾
	ItemNo = no;
	ItemBuffDelegate.Broadcast(ItemNo);
}

void ARunGameStateBase::LifeCalc(int life)
{
	// ���C�t����
	Life -= life;
	LifeDelegate.Broadcast(Life);
}

