// Copyright Epic Games, Inc. All Rights Reserved.

#include "RunGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ScoreItem.h"
#include "BuffItem.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"

namespace MaxPlayerLane
{
	constexpr  int MaxRightLane = 5;
	constexpr int MaxLeftLane = 0;
}

ARunGameCharacter::ARunGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// ?o?t???????C?g????
	PointLightComponent = CreateOptionalDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	PointLightComponent->SetupAttachment(RootComponent);
	PointLightComponent->SetVisibility(false);
	PointLightComponent->Intensity = 15000.0f;
	PointLightComponent->AttenuationRadius = 300.0f;
	PointLightComponent->SetLightColor(FColor::Yellow);

	// ability system component
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	Tags.Add(FName("Player"));
}

void ARunGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameState = GetWorld()->GetGameState<ARunGameStateBase>();
	GameMode = Cast<ARunGameGameMode>(GetWorld()->GetAuthGameMode());

	PlayerLane = GameState->GetLane();

	// ?f???Q?[?g???o?^
	FPowerUpDelegate::FDelegate PowerUpDelegate;
	PowerUpDelegate.BindDynamic(this, &ARunGameCharacter::PlayerPowerUp);
	GameState->SetPowerUpDelegate(PowerUpDelegate);

	FGameStartDelegate::FDelegate GameStartDelegate;
	GameStartDelegate.BindDynamic(this, &ARunGameCharacter::IsMove);
	GameMode->SetGameStartDelegate(GameStartDelegate);

	FGameStartDelegate::FDelegate GameEndDelegate;
	GameEndDelegate.BindDynamic(this, &ARunGameCharacter::IsMove);
	GameMode->SetGameEndDelegate(GameEndDelegate);

	OnActorBeginOverlap.AddDynamic(this, &ARunGameCharacter::OnOverlapBegin);

	// ?A?r???e?B?V?X?e??
	if (AbilitySystem)
	{
		int32 inputID(0);
		if (HasAuthority() && AbilityList.Num() > 0)
		{
			for (auto Ability : AbilityList) 
			{
				if (Ability)
				{
					AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, inputID++));
				}
			}
		}
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}

// Called every frame
void ARunGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(MoveSpeed);
}

void ARunGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARunGameCharacter::PlayerMoveRight);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ARunGameCharacter::PlayerMoveLeft);
}

void ARunGameCharacter::PlayerMoveRight()
{
	// ???[?????[????????????????
	if (GameStart && PlayerLane < MaxPlayerLane::MaxRightLane)
	{
		// ???[????????
		PlayerLane += 1;
		AddActorLocalOffset(FVector(0.0f, 300.0f, 0));

		UGameplayStatics::PlaySound2D(this, RightMoveSound);
		RightMoveSound->VolumeMultiplier = 2.0f;
	}
}

void ARunGameCharacter::PlayerMoveLeft()
{
	// ???[?????[????????????????
	if (GameStart && PlayerLane > MaxPlayerLane::MaxLeftLane)
	{
		// ???[????????
		PlayerLane -= 1;
		AddActorLocalOffset(FVector(0.0f, -300.0f, 0));

		UGameplayStatics::PlaySound2D(this, RightMoveSound);
		RightMoveSound->VolumeMultiplier = 2.0f;
	}
}

void ARunGameCharacter::IsMove()
{
	// ?Q?[????????
	GameStart = GameMode->GamePlay;
	// ???????x????
	MoveSpeed = GameMode->MoveSpeed;
}

void ARunGameCharacter::PlayerPowerUp()
{
	PointLightComponent->SetVisibility(true);

	// ?????_
	TFunction<void(void)> PowerUpLift = [this]() {PointLightComponent->SetVisibility(false); };

	// 3?b????????
	FTimerHandle TimerHandle;
	FTimerManager& TimerManager = GetWorldTimerManager();
	TimerManager.SetTimer(TimerHandle,(TFunction<void(void)>&&)PowerUpLift, 1.0f, false, GameState->PowerUpTime);
}

void ARunGameCharacter::OnOverlapBegin(AActor* PlayerActor, AActor* OtherActor)
{

	if (OtherActor->ActorHasTag("ScoreItem"))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(), FRotator::ZeroRotator, FVector(2.0f, 2.0f, 2.0f));
		Cast<AScoreItem>(OtherActor)->ToCatchItem();
	}
	if (OtherActor->ActorHasTag("BuffItem"))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(), FRotator::ZeroRotator, FVector(2.0f, 2.0f, 2.0f));
		Cast<ABuffItem>(OtherActor)->ToCatchItem();
	}
}

void ARunGameCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystem->RefreshAbilityActorInfo();
}