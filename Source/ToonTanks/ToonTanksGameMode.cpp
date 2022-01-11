// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor) {
	if (DeadActor == Tank) {
		Tank->ManageDestruction();
		if (ToonTanksPlayerController) {
			ToonTanksPlayerController->SetPlayerState(false);
		}
	}
	else if (ATower* Tower = Cast<ATower>(DeadActor)) {
		Tower->ManageDestruction();
	}
}

void AToonTanksGameMode::BeginPlay() {
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart() {

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	if (ToonTanksPlayerController) {
		ToonTanksPlayerController->SetPlayerState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerState,
			true
		);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			InputDelegate,
			StartDelay,
			false
		);
	}	
}