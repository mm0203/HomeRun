// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveEquation.generated.h"

UCLASS()
class RUNGAME_API AWaveEquation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveEquation();

	FVector _u_pre;
	FVector _u_cur;
	FVector _u_new;

	int kWaveGrid = 300;
	int  kWaveWidth = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void reset();
	void step();

	int valueIndex(int x, int y) const { return y * kWaveGrid + x; }
	float value(int x, int y) const { return _u_cur[valueIndex(x, y)]; }
	int widthN() const { return kWaveGrid; }
	int heightN() const { return kWaveGrid; }
	float width() const { return kWaveWidth; }
	float height() const { return kWaveWidth; }

};
