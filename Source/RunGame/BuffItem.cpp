// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffItem.h"
#include "RunGameStateBase.h"
#include "Kismet/GameplayStatics.h"

ABuffItem::ABuffItem()
{
	ItemNo = 0;

	RotationValue = FRotator(.0f, .0f, .0f);

	Tags.Add(FName("BuffItem"));
}

void ABuffItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuffItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(RotationValue * DeltaTime, false, 0, ETeleportType::TeleportPhysics);
}

void ABuffItem::ToCatchItem()
{
	// ‰¹
	UGameplayStatics::PlaySound2D(this, BuffSound);
	BuffSound->VolumeMultiplier = 3.0f;

	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameState->ItemBuff(ItemNo);

	// íœ
	Destroy();
}