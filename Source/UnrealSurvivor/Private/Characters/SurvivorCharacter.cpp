// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/SurvivorCharacter.h"
#include "Components/InputComponent.h" 
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASurvivorCharacter::ASurvivorCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent> (TEXT ("CameraBoom"));
	CameraBoom->SetupAttachment (GetRootComponent ());
	CameraBoom->TargetArmLength = 300.0f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent> (TEXT ("ViewCamera"));
	ViewCamera->SetupAttachment (CameraBoom);
}

// Called when the game starts or when spawned
void ASurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG (LogTemp, Warning, TEXT ("Chal-ing"));
	if (APlayerController* PlayerController = Cast<APlayerController> (Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem> (PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext (SurvivorContext, 0);
		}
	}
}

void ASurvivorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent> (PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction (MovementAction, ETriggerEvent::Triggered, this, &ASurvivorCharacter::Move);
		EnhancedInputComponent->BindAction (LookAction, ETriggerEvent::Triggered, this, &ASurvivorCharacter::Look);
		EnhancedInputComponent->BindAction (JumpAction, ETriggerEvent::Triggered, this, &ASurvivorCharacter::Jump);
	}
}

void ASurvivorCharacter::Move(const FInputActionValue &Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation ();
	const FRotator YawRot (0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDir = FRotationMatrix (YawRot).GetUnitAxis (EAxis::X);
	AddMovementInput (ForwardDir, MovementVector.Y);
	const FVector RightDir = FRotationMatrix (YawRot).GetUnitAxis (EAxis::Y);
	AddMovementInput (RightDir, MovementVector.X);
}

void ASurvivorCharacter::Look(const FInputActionValue &Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput (LookAxisVector.Y);
	AddControllerYawInput (LookAxisVector.X);
}

void ASurvivorCharacter::Jump(const FInputActionValue &Value)
{
	ACharacter::Jump ();
}