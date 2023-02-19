// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();

	UE_LOG(LogTemp, Display, TEXT("%s Spawned"), *CurrentWeapon->GetName());
	// ...

}

void UWeaponComponent::SpawnWeapon() {

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	const FTransform GeometryTransform = FTransform(Character->GetActorRotation(), Character->GetActorLocation());
	UE_LOG(LogTemp, Display, TEXT("%s"), *GeometryTransform.ToString());
	auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass, GeometryTransform);
	if (!Weapon) return;
	Weapon->SetOwner(Character);
	CurrentWeapon = Weapon;
	AttachWeaponToSocket(Weapon,Character->GetMesh(),WeaponArmorySocketName);
	
}

void UWeaponComponent::StartAttack() {
	CurrentWeapon->StartAttack();
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) {
	if (!Weapon || !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}
