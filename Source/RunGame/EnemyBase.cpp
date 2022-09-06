// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "RunGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "RunGameCharacter.h"

AEnemyBase::AEnemyBase()
{
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

		// カメラ揺れ
		APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
		CameraManager->StartCameraShake(CameraShake);

		// プレイヤーの位置
		ARunGameCharacter* MyCharacter = Cast<ARunGameCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		FVector Location = MyCharacter->GetActorLocation();

		if (PowerUp)
		{
			// エフェクト発生
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PowerUpParticle, Location, FRotator::ZeroRotator, FVector(2.0f, 2.0f, 2.0f));
			UGameplayStatics::PlaySound2D(this, PowerUpSound);
			PowerUpSound->VolumeMultiplier = 3.0f;
		}
		else
		{
			// 体力現象
			GameState->LifeCalc(1);
			// エフェクト発生
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NoPowerUpParticle, Location, FRotator::ZeroRotator, FVector(2.0f, 2.0f, 2.0f));
			UGameplayStatics::PlaySound2D(this, NoPowerUpSound);
			NoPowerUpSound->VolumeMultiplier = 3.0f;

			// HPが0
			if(GameState->GetLife() <= 0)
			{
				// ゲーム終了の呼び出し
				auto GameMode = Cast<ARunGameGameMode>(GetWorld()->GetAuthGameMode());
				GameMode->IsGameEnd();
			}
		}

		Destroy();
	}
}