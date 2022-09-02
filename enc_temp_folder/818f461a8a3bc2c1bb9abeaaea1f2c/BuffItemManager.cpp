// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffItemManager.h"
#include "RunGameStateBase.h"

// Sets default values
ABuffItemManager::ABuffItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuffItemManager::BeginPlay()
{
	Super::BeginPlay();
	auto gameState = GetWorld()->GetGameState<ARunGameStateBase>();
	if (gameState != nullptr)
	{
		gameState->ItemBuffDelegate.AddUObject(this, &ABuffItemManager::BuffEffect);
	}
}

// Called every frame
void ABuffItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuffItemManager::BuffEffect(int no)
{
	auto gameState = GetWorld()->GetGameState<ARunGameStateBase>();
	gameState->SetPowerUp(true);

	FTimerHandle TimerHandle;
	FTimerManager& TimerManager = GetWorldTimerManager();
	TimerManager.SetTimer(TimerHandle, this, &ABuffItemManager::PowerUpLift, 1.0f, false, 3.0f);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "PowerUp");
}

void ABuffItemManager::PowerUpLift()
{
	auto gameState = GetWorld()->GetGameState<ARunGameStateBase>();
	gameState->SetPowerUp(false);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "PowerLift");
}


