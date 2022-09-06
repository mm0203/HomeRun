// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "RunGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "RunGameCharacter.h"

AEnemyBase::AEnemyBase()
{
	// �J�v�Z���R���|�[�l���g(DoNotCreateDefaultSubobject�\)
	CollisionComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(FName("OverlapAllDynamic"));

	// ���b�V���R���|�[�l���g
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

		// �J�����h��
		APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
		CameraManager->StartCameraShake(CameraShake);

		// �v���C���[�̈ʒu
		ARunGameCharacter* MyCharacter = Cast<ARunGameCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		FVector Location = MyCharacter->GetActorLocation();

		if (PowerUp)
		{
			// �G�t�F�N�g����
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PowerUpParticle, Location, FRotator::ZeroRotator, FVector(2.0f, 2.0f, 2.0f));
			UGameplayStatics::PlaySound2D(this, PowerUpSound);
			PowerUpSound->VolumeMultiplier = 3.0f;
		}
		else
		{
			// �̗͌���
			GameState->LifeCalc(1);
			// �G�t�F�N�g����
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NoPowerUpParticle, Location, FRotator::ZeroRotator, FVector(2.0f, 2.0f, 2.0f));
			UGameplayStatics::PlaySound2D(this, NoPowerUpSound);
			NoPowerUpSound->VolumeMultiplier = 3.0f;

			// HP��0
			if(GameState->GetLife() <= 0)
			{
				// �Q�[���I���̌Ăяo��
				auto GameMode = Cast<ARunGameGameMode>(GetWorld()->GetAuthGameMode());
				GameMode->IsGameEnd();
			}
		}

		Destroy();
	}
}