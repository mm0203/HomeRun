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

	UFUNCTION()
		void ToCatchItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	// Žæ“¾Žž‚ÌƒXƒRƒA
	UPROPERTY(EditAnywhere)
		int ItemNo;

	UPROPERTY(EditAnywhere, Category = "Rotation")
		FRotator RotationValue;
};
