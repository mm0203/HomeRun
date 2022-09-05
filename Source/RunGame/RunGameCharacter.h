// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/PointLightComponent.h"
#include "RunGameStateBase.h"
#include "RunGameGameMode.h"
#include "AbilitySystemInterface.h"
#include "RunGameCharacter.generated.h"

class ARunGameGameMode;

UCLASS(config=Game)
class ARunGameCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ARunGameCharacter();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// UAbilitySytemComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;

	// 保持するアビリティリスト
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TArray<TSubclassOf<class UGameplayAbility>> AbilityList;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
		UParticleSystem* Particle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPointLightComponent* PointLightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GameStart;

	UPROPERTY(EditAnywhere)
		USoundCue* RunSound;

	UPROPERTY(EditAnywhere)
		USoundCue* RightMoveSound;

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	// 移動
	void PlayerMoveRight();
	void PlayerMoveLeft();

	// キー入力
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(AActor* PlayerActor, AActor* OtherActor);

	// getter
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystem; };

private:
	int PlayerLane;
	FVector MoveSpeed;
	ARunGameGameMode* GameMode;
	ARunGameStateBase* GameState;


};

