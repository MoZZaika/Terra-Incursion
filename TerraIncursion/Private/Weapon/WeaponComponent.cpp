// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Miscs/Utilities.h"
#include "Animations/AnimUtils.h"
#include "Animations/AttackFinishedAnimNotify.h"
#include "Animations/AttackStartedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	InitAnimations();
}

void UWeaponComponent::SpawnWeapon() {
	UWorld* const World = GetWorld();
	CHECK_ERROR(World, TEXT("World is nullptr"))

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	CHECK_ERROR(Character, TEXT("Character is nullptr"))

	const FTransform GeometryTransform = FTransform(Character->GetActorRotation(), Character->GetActorLocation());

	auto Weapon = World->SpawnActor<ABaseWeapon>(WeaponData.WeaponClass);
	CHECK_ERROR(Weapon, TEXT("Weapon is nullptr"))

	Weapon->SetOwner(Character);
	CurrentWeapon = Weapon;

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	CHECK_ERROR(CharacterMesh, TEXT("CharacterMesh is nullptr"))

	AttachWeaponToSocket(Weapon, CharacterMesh, WeaponArmorySocketName);

}

void UWeaponComponent::StartAttack() {

	CHECK_ERROR(CurrentWeapon, TEXT("CurrentWeapon is nullptr"));

	CurrentWeapon->StopAttack();
	PlayAnimMontage(WeaponData.AttackAnimMontage);
	
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) {
	CHECK_ERROR(Weapon, TEXT("Weapon is nullptr"))
	CHECK_ERROR(SceneComponent, TEXT("SceneComponent is nullptr"))

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UWeaponComponent::InitAnimations()
{
	auto AttackFinishedNotify = AnimUtils::FindNotifyByClass<UAttackFinishedAnimNotify>(WeaponData.AttackAnimMontage);
	CHECK_ERROR(AttackFinishedNotify, TEXT("AttackFinishedNotify is nullptr"));
	AttackFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnAttackFinished);

	auto AttackStartedNotify = AnimUtils::FindNotifyByClass<UAttackStartedAnimNotify>(WeaponData.AttackAnimMontage);
	CHECK_ERROR(AttackStartedNotify, TEXT("AttackStartedNotify is nullptr"));
	AttackStartedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnAttackStarted);

}

void UWeaponComponent::OnAttackStarted(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;

	CurrentWeapon->StartAttack();

}

void UWeaponComponent::OnAttackFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;

	CurrentWeapon->StopAttack();

}