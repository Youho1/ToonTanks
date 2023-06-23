// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	float speed = 500.0f;
	UPROPERTY(EditAnywhere)
	float TurnRate = 40.0f;
	UPROPERTY()
	APlayerController* PlayerControllerRef;
	void Move(float Value);
	void Turn(float Value);
protected:
	virtual void BeginPlay() override;
public:
	ATank(); //constructor
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
};
