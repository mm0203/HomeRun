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

private:
	// �擾���̃X�R�A
	UPROPERTY(EditAnywhere)
	int Score;
};
