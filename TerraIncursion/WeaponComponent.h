// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BaseWeapon.h"
#include "WeaponComponent.generated.h"

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
	TSubclassOf<AActor> WeaponClass = nullptr;

	void BeginPlay() override;

	void SpawnWeapon();

	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

};