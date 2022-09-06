// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectBase.h"

AObjectBase::AObjectBase()
{
	// �J�v�Z���R���|�[�l���g(DoNotCreateDefaultSubobject�\)
	CollisionComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(FName("OverlapAllDynamic"));

	// ���b�V���R���|�[�l���g
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(CollisionComponent);
	StaticMeshComponent->SetCollisionProfileName(FName("NoCollision"), false);

	Tags.Add(FName("Object"));
}

void AObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}
