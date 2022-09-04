// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectBase.h"
#include "ScoreItem.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API AScoreItem : public AObjectBase
{
	GENERATED_BODY()
public:
	AScoreItem();

	UFUNCTION()
		void ToCatchItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	// Žæ“¾Žž‚ÌƒXƒRƒA
	UPROPERTY(EditAnywhere)
	int Score;

	FVector startLocation;
	float velocity;


};
