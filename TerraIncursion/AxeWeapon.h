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
		float Roll = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName BladeBegginingSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName BladeEndSocketName;

	FRotator StartAttackRotator;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void StartAttack() override;

	void RayCast();

	void Rotate();

	virtual bool GetBladeTraceData(FVector& TraceStart, FVector& TraceEnd) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
