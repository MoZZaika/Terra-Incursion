// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "TeamMovment")
	float movmentSpeed = 1;

	UPROPERTY(EditDefaultsOnly)
	TArray<USceneComponent*> slots;

	UPROPERTY(EditAnywhere)
	FWarrior warriors [4];

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	FVector moveDirection = FVector::ZeroVector;

	void MoveLeftRight(const float axisValue);
	void MoveForwardBack(const float axisValue);

};
