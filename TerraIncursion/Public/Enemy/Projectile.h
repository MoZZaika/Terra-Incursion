// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.generated.h"

UCLASS()
class TERRAINCURSION_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* staticMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float speed = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float damage = 100.0f;

	FVector movDirection;
	AActor* target = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
