// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	PovCamera = CreateDefaultSubobject<UCameraComponent>("PovCamera");
	PovCamera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveTank);
}

void ATank::MoveTank(float Value) {
	FVector DeltaLocation(0.f);
	DeltaLocation.X = Value;
	AddActorLocalOffset(DeltaLocation);
}