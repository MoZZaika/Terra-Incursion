// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Weapon/WeaponComponent.h"
#include "AIController.h"
#include "Team.generated.h"

class UWeaponComponent;

USTRUCT(BlueprintType)
struct FWarrior
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	USceneComponent* slot = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacter> warriorClass;

	UPROPERTY(EditAnywhere)
	UWeaponComponent* weaponComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float lockTargetDistance = 100.f;

	ACharacter* instance = nullptr;
	AAIController* controller = nullptr;
	AActor* currentTarget = nullptr;
	FTimerHandle* retreatmentTimerHandle;
	bool canRunToSlot = true;



};

UCLASS()
class TERRAINCURSION_API ATeam : public ACharacter
{
	GENERATED_BODY()

public:
	
	ATeam();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	static const uint32 maxWarriorCount = 3;
	FVector moveDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FWarrior warriors[maxWarriorCount];

	UPROPERTY(EditDefaultsOnly)
	float teamMovmentSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* mainSlot = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TArray<USceneComponent*> slots;

	UPROPERTY(EditDefaultsOnly)
	float warriorsRetreatDelay = 3.0f;

	virtual void BeginPlay() override;
	void MoveLeftRight(const float axisValue);
	void MoveForwardBack(const float axisValue);
	void AttackLeft();
	void AttackRight();
	void AttackForward();
	void WarriorMoveToAttack(FWarrior & warrior);
	void WarriorAttack(FWarrior& warrior);
	void FindTarget(FWarrior & warrior);
};
