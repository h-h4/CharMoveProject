// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DrawDebugHelpers.h"



ADefaultCharacter::ADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Comp"));
	SetRootComponent(CapsuleComp);
	CapsuleComp->SetCapsuleHalfHeight(88.0f);
	CapsuleComp->SetCapsuleRadius(34.0f);
	CapsuleComp->SetSimulatePhysics(false);

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Comp"));
	MeshComp->SetupAttachment(CapsuleComp);
	MeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Comp"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}


void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsGrounded) CurrentVelocity.Z += Gravity * DeltaTime;

	FVector Displacement = CurrentVelocity * DeltaTime;
	AddActorWorldOffset(Displacement, true);

	CheckGroundCollision();
}

void ADefaultCharacter::CheckGroundCollision() {
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0.0f, 0.0f, -GroundCheckDistance);

	FCollisionShape SphereShape = FCollisionShape::MakeSphere(GroundCheckRadius);

	FHitResult HitResult;
	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_WorldStatic,
		SphereShape
	);

	if (bHit && CurrentVelocity.Z <= 0.0f) {
		bIsGrounded = true;
		CurrentVelocity.Z = 0.0f;
	}
	else {
		bIsGrounded = false;
	}
}


void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (MoveAction) {
			EnhancedInputComponent->BindAction(
				MoveAction, 
			    ETriggerEvent::Triggered, 
			    this, 
			    &ADefaultCharacter::Move);
		}

		if (LookAction) {
			EnhancedInputComponent->BindAction(
				LookAction,
				ETriggerEvent::Triggered,
				this,
				&ADefaultCharacter::Look);
		}

		if (UpAction) {
			EnhancedInputComponent->BindAction(
				UpAction,
				ETriggerEvent::Triggered,
				this,
				&ADefaultCharacter::Up);
		}

		if (RollAction) {
			EnhancedInputComponent->BindAction(
				RollAction,
				ETriggerEvent::Triggered,
				this,
				&ADefaultCharacter::Roll);
		}
	}
}

void ADefaultCharacter::Move(const FInputActionValue& Value) {
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		float CurrentSpeed = bIsGrounded ? Speed : (Speed * AirControlFactor);

		FVector DeltaLocation = FVector(MovementVector.X, MovementVector.Y, 0.0f) * CurrentSpeed * DeltaTime;
		AddActorLocalOffset(DeltaLocation, true);
	}
}

void ADefaultCharacter::Look(const FInputActionValue& Value) {
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	AddActorLocalRotation(FRotator(0.0f, LookAxisVector.X * Sensitivity, 0.0f));

	if (SpringArmComp) {
		FRotator NewRotation = SpringArmComp->GetRelativeRotation();

		NewRotation.Pitch += LookAxisVector.Y * Sensitivity;
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch, -80.0f, 80.0f);

		SpringArmComp->SetRelativeRotation(NewRotation);
	}
}

void ADefaultCharacter::Up(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FVector LocalUpDir = GetActorUpVector();

	float Thrust = 2000.0f; 

	CurrentVelocity += (LocalUpDir * InputValue * Thrust * DeltaTime);

	CurrentVelocity = CurrentVelocity.GetClampedToMaxSize(2000.0f);
}

void ADefaultCharacter::Roll(const FInputActionValue& Value) {
	float InputValue = Value.Get<float>();
	float RollAmount = InputValue * Sensitivity;

	FRotator RollRotator(0.0f, 0.0f, RollAmount);
	AddActorLocalRotation(RollRotator);
}

void ADefaultCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

#if WITH_EDITOR

	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0.0f, 0.0f, -GroundCheckDistance);

	FlushPersistentDebugLines(GetWorld());

	DrawDebugSphere(
		GetWorld(),
		End,              
		GroundCheckRadius,  
		12,                
		FColor::Green,     
		false,             
		1.0f               
	);
#endif
}