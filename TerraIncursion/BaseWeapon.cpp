// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");

    SetRootComponent(BaseMesh);
    
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseWeapon::StartAttack() {
	UE_LOG(LogTemp, Display, TEXT("attack"));
    isAttack = true;
}

void ABaseWeapon::StopAttack() {
    isAttack = false;
}

void ABaseWeapon::PermamentAttack() {

	FTimerHandle CountdownTimerHandle;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ABaseWeapon::StartAttack, 4.0f, true);
}

bool ABaseWeapon::GetCharacterViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return false;

    ViewRotation = Character->GetController()->GetPawn()->GetActorRotation();
	ViewLocation = Character->GetController()->GetPawn()->GetActorLocation();


    return true;
}

bool ABaseWeapon::GetWeaponTransformData(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return false;

    FTransform Transform = GetTransform();
    ViewRotation = Transform.GetRotation().Rotator();
    ViewLocation = Transform.GetLocation();


    return true;
}


bool ABaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (!GetWeaponTransformData(ViewLocation, ViewRotation)) return false;


    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ABaseWeapon::MakeAttack() {};

void ABaseWeapon::MakeHit(TArray<FHitResult>& HitResults, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;

    FCollisionObjectQueryParams ObjectCollisionParams;
    ObjectCollisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);

    FCollisionQueryParams CollisionParams;
    CollisionParams.bReturnPhysicalMaterial = true;
    CollisionParams.AddIgnoredActor(GetOwner());
    

    //GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
    GetWorld()->LineTraceMultiByObjectType(HitResults, TraceStart, TraceEnd, ObjectCollisionParams, CollisionParams);
}

