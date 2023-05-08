// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BaseWeapon.h"
#include "WeaponComponent.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* AttackAnimMontage;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TERRAINCURSION_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UWeaponComponent();

	void StartAttack();

private:

	ABaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "weapon_r";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FWeaponData WeaponData;

	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();

	void OnAttackFinished(USkeletalMeshComponent* MeshComp);
	void OnAttackStarted(USkeletalMeshComponent* MeshComp);

	void BeginPlay() override;

	void SpawnWeapon();

	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

};