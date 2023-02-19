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
	// Sets default values for this component's properties
	UWeaponComponent();

	void StartAttack();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponArmorySocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<AActor> WeaponClass;

	UPROPERTY()
		ABaseWeapon* CurrentWeapon = nullptr;

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	void SpawnWeapon();


	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

};