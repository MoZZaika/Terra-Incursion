// Fill out your copyright notice in the Description page of Project Settings.


#include "SpearWeapon.h"

// Sets default values
ASpearWeapon::ASpearWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpearWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	PermamentAttack();
}

// Called every frame
void ASpearWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpearWeapon::StartAttack() {
	ABaseWeapon::StartAttack();

	FVector TraceStart, TraceEnd;

	GetTraceData(TraceStart, TraceEnd);

	TArray<FHitResult> HitResults;
	MakeHit(HitResults, TraceStart, TraceEnd);
	DrawLineTraces(GetWorld(), TraceStart, TraceEnd, HitResults, 1.f);
	//DrawDebugDirectionalArrow(GetWorld(), TraceStart, TraceEnd, 120.f, FColor::Magenta, true, -2.f, 0, 5.f);

	for (auto& HitResult : HitResults)
	{
		//if (HitResult.bBlockingHit)
		//{
		UE_LOG(LogTemp, Display, TEXT("Hitted %s"), *HitResult.GetActor()->GetName());
		//}

	}

}

