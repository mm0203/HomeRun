// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "RunGameStateBase.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// カプセルコンポーネント(DoNotCreateDefaultSubobject可能)
	CollisionComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(FName("OverlapAllDynamic"));

	// メッシュコンポーネント
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(CollisionComponent);
	StaticMeshComponent->SetCollisionProfileName(FName("NoCollision"), false);

	Tags.Add(FName("Enemy"));

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::BeginOverlap);
}

void AEnemyBase::BeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
		bool PowerUp = GameState->GetPowerUp();

		if (PowerUp)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "EnemyDown");
			Destroy();
		}
		else
		{
			GameState->ScoreAdd(-300);
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "PlayerDown");
		}
	}
}