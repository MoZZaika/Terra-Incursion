// Fill out your copyright notice in the Description page of Project Settings.


#include "AxeWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogAxeWeapon, Display, All)

// Sets default values
AAxeWeapon::AAxeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAxeWeapon::BeginPlay()
{
	Super::BeginPlay();

	StartAttackRotator = GetActorRotation();

}

// Called every frame
void AAxeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAttack) {

		RayCast();
		Rotate(DeltaTime);

	}

}

void AAxeWeapon::StartAttack() {

	ABaseWeapon::StartAttack();

	if (isAttack) {
		return;
	}

	StartAttackRotator = FRotator(ClockwiseDirection * AttackAngle * 0.5, 0.f, 0.f);
	SetActorRelativeRotation(StartAttackRotator);

}

void AAxeWeapon::Rotate(float DeltaTime) {

	FRotator Rotation = FRotator(-ClockwiseDirection * RotateSpeed * DeltaTime, 0.f, 0.f);
	Angle += RotateSpeed * DeltaTime;

	FQuat QuatRotation = FQuat(Rotation);
	AddActorLocalRotation(Rotation, false, 0, ETeleportType::None);
	
	//UE_LOG(LogAxeWeapon, Display, TEXT("%f"), Angle );
	if ( Angle >= AttackAngle) {
		StopAttack();
	}

}

void AAxeWeapon::StopAttack() {

	Super::StopAttack();

	ClockwiseDirection *= -1;
	StartAttackRotator = FRotator(ClockwiseDirection * AttackAngle * 0.5, 0.f, 0.f);
	SetActorRelativeRotation(StartAttackRotator);
	Angle = 0.f;

	CollisionParams.ClearIgnoredActors();
	CollisionParams.AddIgnoredActor(GetOwner());
}


void AAxeWeapon::RayCast() {

	FVector TraceStart, TraceEnd;

	if (!GetTraceData(TraceStart, TraceEnd)) {
		return;
	};

	TArray<FHitResult> HitResults;
	MakeHit(HitResults, TraceStart, TraceEnd);
	DrawLineTraces(GetWorld(), TraceStart, TraceEnd, HitResults, 0.1f);
	//DrawDebugDirectionalArrow(GetWorld(), TraceStart, TraceEnd, 120.f, FColor::Magenta, true, -2.f, 0, 5.f);

	for (auto& HitResult : HitResults)
	{
		UE_LOG(LogAxeWeapon, Display, TEXT("Hitted %s"), *HitResult.GetActor()->GetName());
		MakeDamage(HitResult);
		CollisionParams.AddIgnoredActor(HitResult.GetActor());
		
	}
	//UE_LOG(LogAxeWeapon, Display, TEXT("\n-----------------\n"));
}

bool AAxeWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	if (!BaseMesh) return false;

	TraceStart = BaseMesh->GetSocketLocation(BladeBegginingSocketName);

	TraceEnd = BaseMesh->GetSocketLocation(BladeEndSocketName);

	return true;
}
	



