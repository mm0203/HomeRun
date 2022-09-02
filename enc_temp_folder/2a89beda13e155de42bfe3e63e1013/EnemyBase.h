// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class RUNGAME_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	AEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
		UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StaticMesh)
		UStaticMeshComponent* StaticMeshComponent;

	// è’ìÀä÷êî
	UFUNCTION()
		void BeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
