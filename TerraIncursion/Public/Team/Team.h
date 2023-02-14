// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "AIController.h"
#include "Team.generated.h"


USTRUCT(BlueprintType)
struct FWarrior
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	USceneComponent* slot;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacter> warriorClass;

	UPROPERTY(EditAnywhere)
	ACharacter* instance;

	UPROPERTY()
	AAIController* controller;
};

UCLASS()
class TERRAINCURSION_API ATeam : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATeam();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	static const uint32 maxWarriorCount = 4;

	UPROPERTY(EditDefaultsOnly, Category = "TeamMovment")
	float movmentSpeed = 1;

	UPROPERTY(EditDefaultsOnly, Category = "TeamMovment")
	float rotationSpeed = 1;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* mainSlot = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TArray<USceneComponent*> slots;

	//UPROPERTY(EditDefaultsOnly)
	TArray<UPrimitiveComponent*> lineTraceToSlots;

	UPROPERTY(EditAnywhere)
	FWarrior warriors [maxWarriorCount];

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	FVector moveDirection = FVector::ZeroVector;

	void MoveLeftRight(const float axisValue);
	void MoveForwardBack(const float axisValue);

};
