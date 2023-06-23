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
private:
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(VisibleAnywhere, Category="Player info")
	class ATank* Player;
	UPROPERTY(EditAnywhere)
	float FireRange = 1000.f;
public:
	virtual void BeginPlay() override;
};
