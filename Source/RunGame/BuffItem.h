// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectBase.h"
#include "Sound/SoundCue.h"
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

	UPROPERTY(EditAnywhere)
		USoundCue* BuffSound;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	// 取得時のスコア
	UPROPERTY(EditAnywhere)
		int ItemNo;

	UPROPERTY(EditAnywhere, Category = "Rotation")
		FRotator RotationValue;
};
