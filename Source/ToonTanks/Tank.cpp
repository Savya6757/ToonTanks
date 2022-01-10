// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	PovCamera = CreateDefaultSubobject<UCameraComponent>("PovCamera");
	PovCamera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveTank);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::TurnTank);
}

void ATank::MoveTank(float Value) {
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector DeltaLocation(0.f);
	DeltaLocation.X = Value * DeltaTime * Speed;
	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::TurnTank(float Value) {
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator DeltaRotation(0.f);
	DeltaRotation.Yaw = Value * DeltaTime * TurnRate;
	AddActorLocalRotation(DeltaRotation, true);
}