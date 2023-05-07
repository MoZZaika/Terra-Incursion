// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AttackTaskNode.h"
#include "Enemy/BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto controller = OwnerComp.GetAIOwner();

	if(!controller)
		return EBTNodeResult::Failed;

	auto actor = Cast<ABaseEnemyCharacter>(controller->GetPawn());

	if (!actor)
		return EBTNodeResult::Failed;

	auto blackBoard = OwnerComp.GetBlackboardComponent();
	if (!blackBoard)
		return EBTNodeResult::Failed;


	auto target = Cast<ACharacter>(blackBoard->GetValueAsObject(playerBlackBoardKey));

	if (!target)
		return EBTNodeResult::Failed;

	const FAttackType attackType = static_cast<FAttackType>(blackBoard->GetValueAsEnum("CurrentAttackType"));

	actor->Attack(target, attackType);

	return EBTNodeResult::Succeeded;
}
