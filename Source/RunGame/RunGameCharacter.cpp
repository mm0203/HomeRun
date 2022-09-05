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

	// set our turn rate for input
	TurnRateGamepad = 50.f;

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


	// �o�t���̃��C�g�ݒ�
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
	PlayerLane = GameState->GetLane();

	GameMode = Cast<ARunGameGameMode>(GetWorld()->GetAuthGameMode());
	MoveSpeed = GameMode->MoveSpeed;

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

	OnActorBeginOverlap.AddDynamic(this, &ARunGameCharacter::OnOverlapBegin);
}

// Called every frame
void ARunGameCharacter::Tick(float DeltaTime)
{
	//auto GameMode = GetWorld()->GetGameState<ARunGameGameMode>();

	GameStart = GameMode->GameOver;

	bool Buff = GameState->GetPowerUp();

	if(Buff)
	{
		PointLightComponent->SetVisibility(true);
	}
	else
	{
		PointLightComponent->SetVisibility(false);
	}

	if (!GameStart)
	{
		AddActorWorldOffset(MoveSpeed);
	}


	Super::Tick(DeltaTime);
}

void ARunGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARunGameCharacter::PlayerMoveRight);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ARunGameCharacter::PlayerMoveLeft);

}

void ARunGameCharacter::PlayerMoveRight()
{
	// ���[���̒[�Ȃ�ړ��ł��Ȃ�
	if (!GameStart && PlayerLane < MaxPlayerLane::MaxRightLane)
	{
		// ���[���̈ړ�
		PlayerLane += 1;
		AddActorLocalOffset(FVector(0.0f, 300.0f, 0));

		UGameplayStatics::PlaySound2D(this, RightMoveSound);
		RightMoveSound->VolumeMultiplier = 2.0f;
	}
}

void ARunGameCharacter::PlayerMoveLeft()
{
	// ���[���̒[�Ȃ�ړ��ł��Ȃ�
	if (!GameStart && PlayerLane > MaxPlayerLane::MaxLeftLane)
	{
		// ���[���̈ړ�
		PlayerLane -= 1;
		AddActorLocalOffset(FVector(0.0f, -300.0f, 0));

		UGameplayStatics::PlaySound2D(this, RightMoveSound);
		RightMoveSound->VolumeMultiplier = 2.0f;
	}
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