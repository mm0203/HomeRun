// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ObjectBase.generated.h"

UCLASS()
class RUNGAME_API AObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StaticMesh)
		UStaticMeshComponent* StaticMeshComponent;

public:	
	virtual void Tick(float DeltaTime) override;

};
