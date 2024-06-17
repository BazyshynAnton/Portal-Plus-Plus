// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;

UCLASS()
class PORTALCOPY_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> MainCharacterContext;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> Movement2D;
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> Look2D;

public:	
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Movement(const FInputActionInstance& Value);
	void Look(const FInputActionInstance& Value);

};
