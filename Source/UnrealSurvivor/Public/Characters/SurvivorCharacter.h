// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SurvivorCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UNREALSURVIVOR_API ASurvivorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASurvivorCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY (EditAnywhere, Category = Input)
	UInputMappingContext* SurvivorContext;

	UPROPERTY (EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY (EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY (EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	void Move (const FInputActionValue& Value);
	void Look (const FInputActionValue& Value);
	void Jump (const FInputActionValue& Value);

private:
	UPROPERTY (VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY (VisibleAnywhere)
	UCameraComponent* ViewCamera;
};
