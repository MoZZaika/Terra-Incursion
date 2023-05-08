// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINCURSION_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	AEnemyAIController();

protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "EnemyAI")
	UAIPerceptionComponent* perception = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnemyAI")
	UBehaviorTree* behaviorTree = nullptr;

	virtual void OnPossess(APawn* InPawn) override;
};
