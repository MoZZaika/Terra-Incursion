// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BaseWeapon.h"
#include "Miscs/Utilities.h"
#include "Kismet/GameplayStatics.h"
#include "Team/Warrior.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    SetRootComponent(BaseMesh);

    CollisionParams.bReturnPhysicalMaterial = true;
   
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::StartAttack() {
    isAttack = true;

    TArray<AActor*> warriors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWarrior::StaticClass(), warriors);

    for (const auto& it : warriors)
    {
        CollisionParams.AddIgnoredActor(it);
    }
}

void ABaseWeapon::StopAttack() {
    isAttack = false;
}

void ABaseWeapon::GetHitResults(TArray<FHitResult>& HitResults, FTraceLine& TraceLIne)
{
    auto World = GetWorld();
    CHECK_ERROR(World,TEXT("World is nullptr"))

    FCollisionObjectQueryParams ObjectCollisionParams;
    ObjectCollisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);  

    World->LineTraceMultiByObjectType(HitResults, TraceLIne.TraceStart, TraceLIne.TraceEnd, ObjectCollisionParams, CollisionParams);
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

