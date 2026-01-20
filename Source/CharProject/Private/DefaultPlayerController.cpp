// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "EnhancedInputSubsystems.h"

ADefaultPlayerController::ADefaultPlayerController() 
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr)
{ 
}

void ADefaultPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
			if (InputMappingContext) {
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}