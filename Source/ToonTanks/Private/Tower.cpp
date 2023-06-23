// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ATank>( UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (Player)
	{
		const float Distance = FVector::Dist(Player->GetActorLocation(), GetActorLocation());
		if (Distance < FireRange)
		{
			// LookAt player
			RotateTurret(Player->GetActorLocation());
		}
		
	}
}
