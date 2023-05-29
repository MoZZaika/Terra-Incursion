// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindEnemyService.generated.h"


class UAIPerceptionComponent;

UCLASS()
class TERRAINCURSION_API UFindEnemyService : public UBTService
{
	GENERATED_BODY()
	
public:
	UFindEnemyService();

protected:
		
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	const FName playerBlackBoardKey = "Player";
	const FName teamTag = "Team";
};
