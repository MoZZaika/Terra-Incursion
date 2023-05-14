// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SelectAttackTypeService.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINCURSION_API USelectAttackTypeService : public UBTService
{
	GENERATED_BODY()

public:
	USelectAttackTypeService();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FName playerBlackBoardKey = "Player";
	
};
