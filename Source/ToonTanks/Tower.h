// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	// Called every frame
	void virtual Tick(float DeltaTime) override;

	void ManageDestruction();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class ATank* Tank;
private:
	UPROPERTY(EditAnywhere)
		float ShootingRange = 700.f;
	FTimerHandle TimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange();
};
