
#include "AxeWeapon.h"
#include "Utilities.h"

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

	FTraceLine TraceLine;

	GetTraceData(TraceLine);

	TArray<FHitResult> HitResults;
	GetHitResults(HitResults, TraceLine);

#ifdef UE_BUILD_DEVELOPMENT
	if (Debug) {
		DrawLineTraces(GetWorld(), TraceLine.TraceStart, TraceLine.TraceEnd, HitResults, 0.1f);
		//DrawDebugDirectionalArrow(GetWorld(), TraceStart, TraceEnd, 120.f, FColor::Magenta, true, -2.f, 0, 5.f);
	}
#endif

	for (auto& HitResult : HitResults)
	{
		AActor* HittedActor = HitResult.GetActor();
		if (!HittedActor) {
			continue;
		}

		UE_LOG(LogAxeWeapon, Display, TEXT("Hitted %s"), *HittedActor->GetName());
		MakeDamage(HitResult);
		CollisionParams.AddIgnoredActor(HittedActor);
		
	}
}

void AAxeWeapon::GetTraceData(FTraceLine& TraceLine) const
{
	CHECK_ERROR(BaseMesh, TEXT("BaseMesh is nullptr"))

	CHECK_ERROR(BaseMesh->DoesSocketExist(BladeBegginingSocketName), TEXT("BladeBegginingSocket doesn't exist"))
	TraceLine.TraceStart = BaseMesh->GetSocketLocation(BladeBegginingSocketName);

	CHECK_ERROR(BaseMesh->DoesSocketExist(BladeEndSocketName), TEXT("BladeEndSocket doesn't exist"))
	TraceLine.TraceEnd = BaseMesh->GetSocketLocation(BladeEndSocketName);
	

}
	



