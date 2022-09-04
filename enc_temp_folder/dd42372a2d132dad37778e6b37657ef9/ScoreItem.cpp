// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreItem.h"
#include "RunGameStateBase.h"

AScoreItem::AScoreItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Score = 0;

	Tags.Add(FName("ScoreItem"));
}
void AScoreItem::BeginPlay()
{
    Super::BeginPlay();

    velocity = 1.0f;
    startLocation = this->GetActorLocation();
}

// Called every frame
void AScoreItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    FVector location = this->GetActorLocation();
    location.Z += velocity;
    if (location.Z < startLocation.Z || location.Z > startLocation.Z + 30.0f) 
    {
        velocity = -velocity;
    }
    this->SetActorLocation(location);
}

void AScoreItem::ToCatchItem()
{
	// ��
	//UGameplayStatics::PlaySound2D(this, ConsumptionSound);

	// �X�R�A�����Z
	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameState->ScoreAdd(Score);

	// �폜
	Destroy();
}
