// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelScript.h"
#include "Camera/CameraActor.h"
#include "RunGameGameMode.h"
#include "Kismet/GameplayStatics.h"


ALevelScript::ALevelScript()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelScript::BeginPlay()
{
	Super::BeginPlay();

	// カメラアクタを取得
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);

	GameMode = Cast<ARunGameGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->GameStartDelegate.AddUObject(this, &ALevelScript::IsMove);
	GameMode->GameEndDelegate.AddUObject(this, &ALevelScript::IsMove);
}

void ALevelScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FoundActors[0]->AddActorWorldOffset(MoveSpeed);
}

void ALevelScript::IsMove()
{
	MoveSpeed = GameMode->MoveSpeed;
}


