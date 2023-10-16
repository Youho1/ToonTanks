// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMesh;
	ProjectileMovementComp = CreateDefaultSubobject<
		UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComp->InitialSpeed = 1300.f;
	ProjectileMovementComp->MaxSpeed = 1300.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	PlayLaunchSound();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* BeingHitActor, UPrimitiveComponent* BeingHitComp,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	const AActor* MyOwner = GetOwner();
	// 発射物の親が存在するか
	if (MyOwner == nullptr)
	{
		Destroy();
	};
	// この発射物を発射した親のコントローラーを取得
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();
	// ダメージを適用する時
	if (BeingHitActor && BeingHitActor != this && BeingHitActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(BeingHitActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				this,
				HitParticles,
				this->GetActorLocation(),
				this->GetActorRotation());
		}
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, this->GetActorLocation());
		}
		if (HitCameraShake)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
		}
	}
	Destroy();
}
// サウンドを再生
void AProjectile::PlayLaunchSound()
{
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, this->GetActorLocation());
	}
}
