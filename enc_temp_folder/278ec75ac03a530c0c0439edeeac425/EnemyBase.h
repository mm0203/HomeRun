// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectBase.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API AEnemyBase : public AObjectBase
{
	GENERATED_BODY()

public:
	AEnemyBase();

	// è’ìÀä÷êî
	UFUNCTION()
		void BeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
