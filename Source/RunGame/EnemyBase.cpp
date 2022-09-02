// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "RunGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "RunGameCharacter.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

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

		if (PowerUp)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "EnemyDown");
		}
		else
		{
			GameState->ScoreAdd(-300);
			// �G�t�F�N�g����

			APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
			CameraManager->StartCameraShake(CameraShake);

			ARunGameCharacter* MyCharacter = Cast<ARunGameCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
			FVector Location = MyCharacter->GetActorLocation();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Location, FRotator::ZeroRotator, FVector(2.0f, 2.0f, 2.0f));

			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "PlayerDown");
		}

		Destroy();
	}
}