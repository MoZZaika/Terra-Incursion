// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TITaskNode.generated.h"



class ABaseEnemyCharacter;

UCLASS()
class TERRAINCURSION_API UTITaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	

protected:

	UBlackboardComponent* GetBlackBoardComponent(UBehaviorTreeComponent& OwnerComp) const;
	ABaseEnemyCharacter* GetActor(const UBehaviorTreeComponent& OwnerComp) const;
};
