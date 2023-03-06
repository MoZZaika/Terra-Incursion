
#include "AxeWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogAxeWeapon, Display, All)

AAxeWeapon::AAxeWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAxeWeapon::BeginPlay()
{
	Super::BeginPlay();

	StartAttackRotator = GetActorRotation();
}

void AAxeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAttack) {
		MakeHit();
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


void AAxeWeapon::MakeHit() {

	FVector TraceStart, TraceEnd;

	if (!GetTraceData(TraceStart, TraceEnd)) {
		return;
	};

	TArray<FHitResult> HitResults;
	GetHitResults(HitResults, TraceStart, TraceEnd);
	DrawLineTraces(GetWorld(), TraceStart, TraceEnd, HitResults, 0.1f);
	//DrawDebugDirectionalArrow(GetWorld(), TraceStart, TraceEnd, 120.f, FColor::Magenta, true, -2.f, 0, 5.f);

	for (auto& HitResult : HitResults)
	{
		AActor* HittedActor = HitResult.GetActor();
		if (!HittedActor) {
			return;
		}

		UE_LOG(LogAxeWeapon, Display, TEXT("Hitted %s"), *HittedActor->GetName());
		MakeDamage(HitResult);
		CollisionParams.AddIgnoredActor(HittedActor);
		
	}
}

bool AAxeWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	if (!BaseMesh) return false;

	TraceStart = BaseMesh->GetSocketLocation(BladeBegginingSocketName);

	TraceEnd = BaseMesh->GetSocketLocation(BladeEndSocketName);

	return true;
}
	



