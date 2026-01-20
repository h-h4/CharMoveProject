// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerChar.h"

// Sets default values
AMyPlayerChar::AMyPlayerChar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

