// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RotateToTargetTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINCURSION_API URotateToTargetTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FName playerBlackBoardKey = "Player";
	FName patrolPointBlackBoardKey = "PatrolPoint";

};
