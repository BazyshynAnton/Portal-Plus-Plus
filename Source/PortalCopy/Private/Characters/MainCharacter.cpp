// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"



AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Rotation the Character on The Axis
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	// Orient Rotation Movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	// Jump Height / Velocity
	GetCharacterMovement()->JumpZVelocity = 300.f;

	// Camera - 1st Person
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh(), FName("head"));

	// Possess player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Mapping Context
	if (TObjectPtr<APlayerController> PlayerController = CastChecked<APlayerController>(GetController()))
	{
		if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> LocalSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			LocalSubsystem->AddMappingContext(MainCharacterContext, 0);
		}
	}
	
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Bind Actions using Enhanced Input
	if (TObjectPtr<UEnhancedInputComponent> PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PlayerInput->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMainCharacter::Movement);
		PlayerInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		PlayerInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
	}

}

// Callback Function for Movement2D Action
void AMainCharacter::Movement(const FInputActionInstance& Value)
{
	const FVector2D Moving = Value.GetValue().Get<FVector2D>();

	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation{ 0.f, ControlRotation.Yaw, 0.f };

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Forward, Moving.Y);

	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Right, Moving.X);
}

// Callback Function for Look2D Action
void AMainCharacter::Look(const FInputActionInstance& Value)
{
	const FVector2D Looking = Value.GetValue().Get<FVector2D>();

	AddControllerPitchInput(Looking.Y);
	AddControllerYawInput(Looking.X);
}

void AMainCharacter::Jump()
{
	Super::Jump();
}
