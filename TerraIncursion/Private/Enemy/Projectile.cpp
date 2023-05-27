// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Team/Warrior.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(staticMeshComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> warriors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWarrior::StaticClass(), warriors);

	float minDistance = ~0U;
	const FVector position = GetActorLocation();
	FVector targetPos = FVector::ZeroVector;
	int32 index = 0;

	for (const auto it : warriors)
	{
		float distance = (position - it->GetActorLocation()).Size();
		if (distance < minDistance)
		{
			minDistance = distance;
			target = warriors[index];
			targetPos = target->GetActorLocation();
		}
		++index;
	}

	if (!targetPos.IsZero())
	{
		movDirection = (targetPos - position).GetSafeNormal();
		SetLifeSpan(5);
	}
	else
	{
		Destroy();
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + movDirection * speed * DeltaTime);

	if ((target->GetActorLocation() - GetActorLocation()).Size() <= 150)
	{
		target->TakeDamage(damage, FDamageEvent(), nullptr, this);
		Destroy();
	}
}

