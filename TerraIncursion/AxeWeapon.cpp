// Fill out your copyright notice in the Description page of Project Settings.


#include "AxeWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogAxeWeapon, All, All)

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

	FVector Location;
	FRotator Rotation;
	GetCharacterViewPoint(Location,Rotation);
	/*Rotation = OldRotation.Add(0.0f, 0.0f, -90.f);
	Rotation = OldRotation.Add(0.0f, 0.5 * AttackAngle, 0.f);*/
	//StartAttackRotator = OldRotation;
	//PermamentAttack();
}

// Called every frame
void AAxeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAttack) {

		RayCast();

	}

}

void AAxeWeapon::StartAttack() {

	ABaseWeapon::StartAttack();


	//FTransform Transform = GetActorTransform();
	//FRotator OldRotation = Transform.GetRotation().Rotator();
	
	//FRotator NewRotation = FRotator(StartAttackRotator.Pitch, StartAttackRotator.Yaw + 0.5f * AttackAngle, StartAttackRotator.Roll);
	//SetActorRotation(StartAttackRotator, ETeleportType::ResetPhysics);
	//UE_LOG(LogTemp, Display, TEXT("attack rotation %s"), *NewRotation.ToString());
}

void AAxeWeapon::Rotate() {
	FTransform Transform = GetActorTransform();
	FRotator OldRotation = Transform.GetRotation().Rotator();


	FRotator Rotation = FRotator(Roll, 0.f, 0.0f);
	FQuat QuatRotation = FQuat(Rotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

	if (FMath::Abs(GetActorRotation().Pitch - StartAttackRotator.Pitch) >= AttackAngle) { StopAttack(); return; }
}

void AAxeWeapon::RayCast() {
	FVector TraceStart, TraceEnd;

	GetBladeTraceData(TraceStart, TraceEnd);

	TArray<FHitResult> HitResults;
	MakeHit(HitResults, TraceStart, TraceEnd);
	DrawLineTraces(GetWorld(), TraceStart, TraceEnd, HitResults, 1.f);
	//DrawDebugDirectionalArrow(GetWorld(), TraceStart, TraceEnd, 120.f, FColor::Magenta, true, -2.f, 0, 5.f);

	for (auto& HitResult : HitResults)
	{
		UE_LOG(LogAxeWeapon, Display, TEXT("Hitted %s"), *HitResult.GetActor()->GetName());
		
	}
	UE_LOG(LogAxeWeapon, Display, TEXT("\n"));
}

bool AAxeWeapon::GetBladeTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	if (!BaseMesh) return false;

	TraceStart = BaseMesh->GetSocketLocation(BladeBegginingSocketName);

	TraceEnd = BaseMesh->GetSocketLocation(BladeEndSocketName);

	return true;
}
	



