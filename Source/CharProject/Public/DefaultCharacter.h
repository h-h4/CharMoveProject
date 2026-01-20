// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCharacter.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS()
class CHARPROJECT_API ADefaultCharacter : public APawn
{
	GENERATED_BODY()

public:
	ADefaultCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* UpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* RollAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")
	bool bIsGrounded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Physics")
	float GroundCheckRadius = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Physics")
	float GroundCheckDistance = 5.0f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")
	float Gravity = -980.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float Sensitivity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float AirControlFactor = 0.5f;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Up(const FInputActionValue& Value);
	void Roll(const FInputActionValue& Value);


	void CheckGroundCollision();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
