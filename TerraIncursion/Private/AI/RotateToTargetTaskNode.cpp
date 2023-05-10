// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RotateToTargetTaskNode.h"
#include "Enemy/BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type URotateToTargetTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;

	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto controller = OwnerComp.GetAIOwner();

	if (!controller)
		return EBTNodeResult::Failed;

	auto actor = Cast<ABaseEnemyCharacter>(controller->GetPawn());

	if (!actor)
		return EBTNodeResult::Failed;

	auto blackBoard = OwnerComp.GetBlackboardComponent();
	if (!blackBoard)
		return EBTNodeResult::Failed;


	auto target = Cast<ACharacter>(blackBoard->GetValueAsObject(playerBlackBoardKey));
	auto patrolPoint = blackBoard->GetValueAsVector(patrolPointBlackBoardKey);

	if (!target && patrolPoint.IsZero())
		return EBTNodeResult::Failed;

	const auto forwardVector = actor->GetActorForwardVector();
	FVector directionToTarget;
	if(target)
		directionToTarget = (target->GetActorLocation() - actor->GetActorLocation()).GetSafeNormal();
	else
		directionToTarget = (patrolPoint - actor->GetActorLocation()).GetSafeNormal();

	const auto product = FVector::CrossProduct(forwardVector, directionToTarget);

	const float angle = FMath::RadiansToDegrees(product.Size() * FMath::Sign(product.Z));

	FRotator NewRotation = FRotator(0, FMath::Min(angle, FMath::DegreesToRadians(5.0f)),0);
	FQuat QuatRotation = FQuat(NewRotation);
	actor->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

	return EBTNodeResult::InProgress;
}

void URotateToTargetTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	auto controller = OwnerComp.GetAIOwner();

	if (!controller)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	auto actor = Cast<ABaseEnemyCharacter>(controller->GetPawn());

	if (!actor)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	auto blackBoard = OwnerComp.GetBlackboardComponent();
	if (!blackBoard)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	auto target = Cast<ACharacter>(blackBoard->GetValueAsObject(playerBlackBoardKey));
	auto patrolPoint = blackBoard->GetValueAsVector(patrolPointBlackBoardKey);

	if (!target && patrolPoint.IsZero())
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	const auto forwardVector = actor->GetActorForwardVector();
	FVector directionToTarget;
	if (target)
		directionToTarget = (target->GetActorLocation() - actor->GetActorLocation()).GetSafeNormal();
	else
		directionToTarget = (patrolPoint - actor->GetActorLocation()).GetSafeNormal();

	const auto product = FVector::CrossProduct(forwardVector, directionToTarget);

	const float angle = FMath::RadiansToDegrees(product.Size() * FMath::Sign(product.Z));

	if (angle < 5)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	FRotator NewRotation = FRotator(0, FMath::Min(angle, FMath::DegreesToRadians(360.0f *DeltaSeconds * 100)), 0);
	FQuat QuatRotation = FQuat(NewRotation);
	actor->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}
