// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (InFireRange())
	{
		RotateTurret(Player->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if (Player == nullptr)
	{
		return;
	}
	if (InFireRange() && Player->bAlive)
	{
		Fire();
	}
}

float ATower::CheckDistanceFromPlayer() const
{
	return FVector::Dist(Player->GetActorLocation(), GetActorLocation());
}

bool ATower::InFireRange() const
{
	if (Player)
	{
		return CheckDistanceFromPlayer() <= FireRange;
	}
	return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	// 自分自身を削除
	Destroy();
}
