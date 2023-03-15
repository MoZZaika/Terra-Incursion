// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Miscs/Utilities.h"

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
	UWorld* const World = GetWorld();
	CHECK_ERROR(World, TEXT("World is nullptr"))

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	CHECK_ERROR(Character, TEXT("Character is nullptr"))

	const FTransform GeometryTransform = FTransform(Character->GetActorRotation(), Character->GetActorLocation());

	auto Weapon = World->SpawnActor<ABaseWeapon>(WeaponClass);
	CHECK_ERROR(Weapon, TEXT("Weapon is nullptr"))

	Weapon->SetOwner(Character);
	CurrentWeapon = Weapon;

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	CHECK_ERROR(CharacterMesh, TEXT("CharacterMesh is nullptr"))

	AttachWeaponToSocket(Weapon, CharacterMesh, WeaponArmorySocketName);

}

void UWeaponComponent::StartAttack() {

	CHECK_ERROR(CurrentWeapon, TEXT("CurrentWeapon is nullptr"));
	CurrentWeapon->StartAttack();
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) {
	CHECK_ERROR(Weapon, TEXT("Weapon is nullptr"))
	CHECK_ERROR(SceneComponent, TEXT("SceneComponent is nullptr"))

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}