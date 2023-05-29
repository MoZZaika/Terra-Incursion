// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SelectAttackTypeService.h"
#include "AIController.h"
#include "Enemy/BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

USelectAttackTypeService::USelectAttackTypeService()
{
}

void USelectAttackTypeService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto actor = Cast<ABaseEnemyCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (!actor)
		return;

	const auto blackBoard = OwnerComp.GetBlackboardComponent();

	if (!blackBoard)
		return;

	auto target = Cast<AActor>(blackBoard->GetValueAsObject("Player"));

	if (!target)
		return;

	if (!actor->GetRangedAttack())
	{
		blackBoard->SetValueAsEnum("CurrentAttackType", static_cast<uint8>(FAttackType::MELEE));
		return;
	}

	float distance = (target->GetActorLocation() - actor->GetActorLocation()).Size();

	if(actor->GetRangedAttackDistance() < distance)
		blackBoard->SetValueAsEnum("CurrentAttackType", static_cast<uint8>(FAttackType::RANGE));
	else
		blackBoard->SetValueAsEnum("CurrentAttackType", static_cast<uint8>(FAttackType::MELEE));

}
