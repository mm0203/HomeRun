// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "RunGameStateBase.h"

AEnemyBase::AEnemyBase()
{
	Tags.Add(FName("Enemy"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::BeginOverlap);
}

void AEnemyBase::BeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameState->ScoreAdd(-300);
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "EnemyHit");
}