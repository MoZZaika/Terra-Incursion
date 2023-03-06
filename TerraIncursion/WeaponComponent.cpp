// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UWeaponComponent::SpawnWeapon() {

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;
	const FTransform GeometryTransform = FTransform(Character->GetActorRotation(), Character->GetActorLocation());

	auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	if (!Weapon) return;

	Weapon->SetOwner(Character);
	CurrentWeapon = Weapon;

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	if (!CharacterMesh) return;
	AttachWeaponToSocket(Weapon, CharacterMesh, WeaponArmorySocketName);

}

void UWeaponComponent::StartAttack() {
	CurrentWeapon->StartAttack();
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) {
	if (!Weapon || !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}