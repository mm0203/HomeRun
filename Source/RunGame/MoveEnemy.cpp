// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveEnemy.h"
#include "Kismet/KismetMathLibrary.h"

AMoveEnemy::AMoveEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// メッシュコンポーネント
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	MoveVelocity = FVector(0, 0, 0);
}

void AMoveEnemy::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddDynamic(this, &AMoveEnemy::OnHit);
}

void AMoveEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(MoveVelocity);
}

void AMoveEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 敵の跳ね返り
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, "EnemyWall");
	MoveVelocity = UKismetMathLibrary::MirrorVectorByNormal(MoveVelocity, -MoveVelocity);
}
