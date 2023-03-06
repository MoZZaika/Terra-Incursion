// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "BaseWeapon.generated.h"

UCLASS()
class TERRAINCURSION_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseWeapon();

	virtual void StartAttack();

	virtual void StopAttack();

protected:

	FCollisionQueryParams CollisionParams;
	bool isAttack = false;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	float WeaponDamage = 10.f;


	virtual void BeginPlay() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	virtual void MakeDamage(const FHitResult& HitResult);

	virtual AController* GetController() const;

	void GetHitResults(TArray<FHitResult>& HitResults, const FVector& TraceStart, const FVector& TraceEnd);

};
