// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreItemWidget.h"
#include "ScoreManager.generated.h"

UCLASS()
class RUNGAME_API AScoreManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AScoreManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UScoreItemWidget* ScoreInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
