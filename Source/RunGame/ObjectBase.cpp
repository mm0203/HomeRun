// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectBase.h"

AObjectBase::AObjectBase()
{
	// カプセルコンポーネント(DoNotCreateDefaultSubobject可能)
	CollisionComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(FName("OverlapAllDynamic"));

	// メッシュコンポーネント
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(CollisionComponent);
	StaticMeshComponent->SetCollisionProfileName(FName("NoCollision"), false);

	Tags.Add(FName("Object"));
}

void AObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}
