// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == nullptr) return;
	if (DeadActor == Player)
	{
		Player->HandleDestruction();
		if (const auto PlayerController = Player->GetTankPlayerController())
		{
			Player->DisableInput(PlayerController);
			PlayerController->bShowMouseCursor = false;
		}
	}
	else if (const auto DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}
