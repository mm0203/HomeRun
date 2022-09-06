// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TitleWidget.h"
#include "TitleManager.generated.h"

UCLASS()
class RUNGAME_API ATitleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATitleManager();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<UUserWidget> WidgetClass;

	void OnStartClicked();

private:
	UTitleWidget* WidgetInstance;

};
