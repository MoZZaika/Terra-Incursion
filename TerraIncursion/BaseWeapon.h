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

	virtual void StartAttack();

	virtual void StopAttack();

	void PermamentAttack();


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		bool isAttack = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void MakeAttack();

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	bool GetCharacterViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	bool GetWeaponTransformData(FVector& ViewLocation, FRotator& ViewRotation) const;

	void MakeHit(TArray<FHitResult>& HitResults, const FVector& TraceStart, const FVector& TraceEnd);





};
