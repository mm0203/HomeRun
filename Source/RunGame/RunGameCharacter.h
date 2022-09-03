// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/PointLightComponent.h"
#include "RunGameStateBase.h"
#include "RunGameGameMode.h"
#include "RunGameCharacter.generated.h"

class ARunGameGameMode;

UCLASS(config=Game)
class ARunGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


public:
	ARunGameCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
		UParticleSystem* Particle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPointLightComponent* PointLightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GameStart;

protected:
	virtual void BeginPlay() override;

	// à⁄ìÆ
	void PlayerMoveRight();
	void PlayerMoveLeft();

	// ÉLÅ[ì¸óÕ
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(AActor* PlayerActor, AActor* OtherActor);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	int PlayerLane;
	FVector MoveSpeed;
	ARunGameGameMode* GameMode;
	ARunGameStateBase* GameState;
};

