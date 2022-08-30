// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"
#include "RunGameStateBase.h"

// Sets default values
AScoreManager::AScoreManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScoreManager::BeginPlay()
{
	Super::BeginPlay();


    TSubclassOf<UUserWidget> WidgetClass;
    WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(TEXT("/Game/ThirdPerson/Blueprints/WBP/WBP_Score.WBP_Score_C"))).LoadSynchronous();
    ScoreInstance = CreateWidget<UGameScore>(GetWorld(), WidgetClass);
    ensure(ScoreInstance);
    if (ScoreInstance)
    {
        ScoreInstance->AddToViewport();
        ScoreInstance->UpdateScore(0);
    }


	auto gameState = GetWorld()->GetGameState<ARunGameStateBase>();
    if (gameState != nullptr)
    {
        gameState->ScoreUpdateDelegate.AddUObject(ScoreInstance, &UGameScore::UpdateScore);
    }
}

// Called every frame
void AScoreManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

