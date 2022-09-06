// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MoveEnemy.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API AMoveEnemy : public AEnemyBase
{
	GENERATED_BODY()
public:
	AMoveEnemy();

protected:
	virtual void BeginPlay() override;

	// à⁄ìÆï˚å¸
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector MoveVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UFloatingPawnMovement* FloatingPawnMovement;

public:

	virtual void Tick(float DeltaTime) override;

	// è’ìÀä÷êî
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
