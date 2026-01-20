// Fill out your copyright notice in the Description page of Project Settings.


#include "GMode_Default.h"
#include "DefaultCharacter.h"
#include "DefaultPlayerController.h"

AGMode_Default::AGMode_Default() {
	DefaultPawnClass = ADefaultCharacter::StaticClass();

	PlayerControllerClass = ADefaultPlayerController::StaticClass();
}