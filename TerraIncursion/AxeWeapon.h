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

	virtual void StartAttack() override;

	virtual void StopAttack() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float AttackAngle = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float RotateSpeed = 0.5f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		FName BladeBegginingSocketName = "blade_start";

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		FName BladeEndSocketName = "blade_end";

	float Angle = 0.f;

	float ClockwiseDirection = -1.f;

	FRotator StartAttackRotator;

	virtual void BeginPlay() override;

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	virtual void Tick(float DeltaTime) override;

	void MakeHit();

	void Rotate(float DeltaTime);

};
