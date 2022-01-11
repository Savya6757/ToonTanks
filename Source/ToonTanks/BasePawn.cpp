// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(TurretMesh);
}	

void ABasePawn::RotateTurret(FVector LocationOfTarget) {
	FVector FinalTargetLocation = LocationOfTarget - TurretMesh->GetComponentLocation();
	FRotator RotateToLocation = FRotator(0.f, FinalTargetLocation.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(RotateToLocation);
}

void ABasePawn::Fire() {
	FVector Location = ProjectileSpawn->GetComponentLocation();
	FRotator Rotation = ProjectileSpawn->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);

}

void ABasePawn::ManageDestruction() {
	// Add effects and stuff
}




