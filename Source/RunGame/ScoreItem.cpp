// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreItem.h"
#include "RunGameStateBase.h"
#include "Kismet/GameplayStatics.h"

AScoreItem::AScoreItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Score = 0;

	Tags.Add(FName("ScoreItem"));
}
void AScoreItem::BeginPlay()
{
    Super::BeginPlay();

    velocity = 0.8f;
    startLocation = this->GetActorLocation();
}

// Called every frame
void AScoreItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    FVector location = this->GetActorLocation();
    location.Z += velocity;
    if (location.Z < startLocation.Z || location.Z > startLocation.Z + 40.0f) 
    {
        velocity = -velocity;
    }
    this->SetActorLocation(location);
}

void AScoreItem::ToCatchItem()
{
	// ‰¹
	UGameplayStatics::PlaySound2D(this, ScoreSound);
    ScoreSound->VolumeMultiplier = 3.0f;

	// ƒXƒRƒA‚ğ‰ÁZ
	auto GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameState->ScoreAdd(Score);

	// íœ
	Destroy();
}
