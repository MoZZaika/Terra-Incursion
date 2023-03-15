// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "CollisionDebugDrawingPublic.h"
#include "SpearWeapon.generated.h"

UCLASS()
class TERRAINCURSION_API ASpearWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpearWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void StartAttack() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
