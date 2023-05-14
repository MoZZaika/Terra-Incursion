// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "BaseWeapon.generated.h"

USTRUCT()
struct FTraceLine
{
	GENERATED_BODY();

public:

	UPROPERTY()
	FVector TraceStart;

	UPROPERTY()
	FVector TraceEnd;

};

UCLASS(Abstract)
class TERRAINCURSION_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseWeapon();

	virtual void StartAttack();

	virtual void StopAttack();

	float GetWeaponAttackDistance();

protected:

	FCollisionQueryParams CollisionParams;
	bool isAttack = false;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	float WeaponDamage = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float WeaponAttackDistance = 100.f;

	UPROPERTY(EditAnywhere)
	bool Debug = true;

	virtual void BeginPlay() override;

	virtual void GetTraceData(FTraceLine & TraceLine) const
	PURE_VIRTUAL(ABaseWeapon::GetTraceData);

	virtual void MakeDamage(const FHitResult& HitResult);

	virtual AController* GetController() const;

	void GetHitResults(TArray<FHitResult>& HitResults, FTraceLine& TraceLine);


};
