// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    SetRootComponent(BaseMesh);

    CollisionParams.bReturnPhysicalMaterial = true;
    CollisionParams.AddIgnoredActor(GetOwner());
    
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::StartAttack() {
    isAttack = true;
}

void ABaseWeapon::StopAttack() {
    isAttack = false;
}

bool ABaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const { return false; }

void ABaseWeapon::GetHitResults(TArray<FHitResult>& HitResults, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;

    FCollisionObjectQueryParams ObjectCollisionParams;
    ObjectCollisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);    

    GetWorld()->LineTraceMultiByObjectType(HitResults, TraceStart, TraceEnd, ObjectCollisionParams, CollisionParams);
}


void ABaseWeapon::MakeDamage(const FHitResult& HitResult) {
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamagedActor->TakeDamage(WeaponDamage, PointDamageEvent, GetController(), this);
}

AController* ABaseWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

