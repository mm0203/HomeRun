// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffItem.h"

#include "RunGameStateBase.h"

ABuffItem::ABuffItem()
{
	ItemNo = 0;

	Tags.Add(FName("BuffItem"));
}

void ABuffItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABuffItem::ToCatchItem()
{
	// ‰¹
	//UGameplayStatics::PlaySound2D(this, ConsumptionSound);

	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameState->ItemBuff(ItemNo);

	// íœ
	Destroy();
}