// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)
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

	UE_LOG(LogWeaponComponent, Display, TEXT("%s Spawned"), *CurrentWeapon->GetName());
}

void UWeaponComponent::SpawnWeapon() {

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;
	const FTransform GeometryTransform = FTransform(Character->GetActorRotation(), Character->GetActorLocation());

	auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	if (!Weapon) return;

	Weapon->SetActorScale3D(WeaponClass->GetDefaultObject<ABaseWeapon>()->GetActorRelativeScale3D());
	Weapon->SetOwner(Character);
	CurrentWeapon = Weapon;
	AttachWeaponToSocket(Weapon,Character->GetMesh(),WeaponArmorySocketName);
	

}

void UWeaponComponent::StartAttack() {
	CurrentWeapon->StartAttack();
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) {
	if (!Weapon || !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}