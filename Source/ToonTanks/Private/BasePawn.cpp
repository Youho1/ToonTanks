// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(const FVector LookAtTarget)
{
	const auto TurretLocation = TurretMesh->GetComponentLocation();
	// ToTarget = ターゲットの座標　-　自分がいる座標
	const auto ToTarget = LookAtTarget - TurretLocation;
	// 地面と平行したいので、Yawだけを回転したい
	const FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	const auto CurrentRotation = TurretMesh->GetComponentRotation();
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			CurrentRotation,
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			InterpSpeed),true);
}

void ABasePawn::Fire()
{
	if (ProjectileSpawnPoint)
	{
		DrawDebugSphere(
			GetWorld(),
			ProjectileSpawnPoint->GetComponentLocation(),
			25.f,
			12,
			FColor::Orange,
			false,
			3.f);
	}
}


