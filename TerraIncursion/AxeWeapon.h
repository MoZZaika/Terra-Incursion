// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "CollisionDebugDrawingPublic.h"
#include "AxeWeapon.generated.h"

class UStaticMeshComponent;

UCLASS()
class TERRAINCURSION_API AAxeWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAxeWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float AttackAngle = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float RotateSpeed = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName BladeBegginingSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName BladeEndSocketName;

	float Angle = 0.f;

	float ClockwiseDirection = -1.f;

	FRotator StartAttackRotator;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void StartAttack() override;

	virtual void StopAttack() override;

	void RayCast();

	void Rotate(float DeltaTime);

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
