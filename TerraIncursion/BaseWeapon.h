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
	// Sets default values for this actor's properties
	ABaseWeapon();

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
		float WeaponDamage = 10.f;

	virtual void StartAttack();

	virtual void StopAttack();



protected:

	bool isAttack = false;

	FCollisionQueryParams CollisionParams;
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MakeAttack();

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	virtual void MakeDamage(const FHitResult& HitResult);

	virtual AController* GetController() const;

	void MakeHit(TArray<FHitResult>& HitResults, const FVector& TraceStart, const FVector& TraceEnd);

};
