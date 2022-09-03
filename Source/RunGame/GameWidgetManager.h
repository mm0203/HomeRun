// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameWidget.h"
#include "GameWidgetManager.generated.h"

UCLASS()
class RUNGAME_API AGameWidgetManager : public AActor
{
	GENERATED_BODY()
	
public:
	AGameWidgetManager();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<UUserWidget> WidgetClass;

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UGameWidget* WidgetInstance;
};
