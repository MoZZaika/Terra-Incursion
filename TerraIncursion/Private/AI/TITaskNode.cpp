// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TITaskNode.h"
#include "AIController.h"
#include "Enemy/BaseEnemyCharacter.h"

UBlackboardComponent* UTITaskNode::GetBlackBoardComponent(UBehaviorTreeComponent& OwnerComp) const
{
	auto blackBoard = OwnerComp.GetBlackboardComponent();
	
	if (!blackBoard)
		return nullptr;

	return blackBoard;
}

ABaseEnemyCharacter* UTITaskNode::GetActor(const UBehaviorTreeComponent& OwnerComp) const
{
	const auto controller = OwnerComp.GetAIOwner();

	if (!controller)
		return nullptr;

	return Cast<ABaseEnemyCharacter>(controller->GetPawn());
}
