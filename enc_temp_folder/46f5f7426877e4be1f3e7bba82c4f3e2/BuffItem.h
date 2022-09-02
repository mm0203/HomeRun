// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectBase.h"
#include "BuffItem.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API ABuffItem : public AObjectBase
{
	GENERATED_BODY()
public:
	ABuffItem();

	virtual void BeginPlay() override;

	UFUNCTION()
		void ToCatchItem();

private:
	// Žæ“¾Žž‚ÌƒXƒRƒA
	UPROPERTY(EditAnywhere)
		int ItemNo;
};
