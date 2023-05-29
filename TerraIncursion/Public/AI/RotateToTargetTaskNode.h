// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TITaskNode.h"
#include "RotateToTargetTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINCURSION_API URotateToTargetTaskNode : public UTITaskNode
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	const FName playerBlackBoardKey = "Player";
	const FName patrolPointBlackBoardKey = "PatrolPoint";

};
