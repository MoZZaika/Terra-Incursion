// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TITaskNode.h"
#include "AttackTaskNode.generated.h"
/**
 * 
 */
UCLASS()
class TERRAINCURSION_API UAttackTaskNode : public UTITaskNode
{
	GENERATED_BODY()
	

public:
	
	UPROPERTY(EditAnywhere)
	float attackRange = 500.0f;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	FName playerBlackBoardKey = "Player";
};
