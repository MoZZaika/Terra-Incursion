// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RotateToTargetTaskNode.h"
#include "Enemy/BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type URotateToTargetTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;

	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto actor = GetActor(OwnerComp);

	if (!actor)
		return EBTNodeResult::Failed;

	auto blackBoard = GetBlackBoardComponent(OwnerComp);
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

	auto actor = GetActor(OwnerComp);

	if (!actor)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	auto blackBoard = GetBlackBoardComponent(OwnerComp);
	if (!blackBoard)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	auto target = Cast<ACharacter>(blackBoard->GetValueAsObject(playerBlackBoardKey));
	auto patrolPoint = blackBoard->GetValueAsVector(patrolPointBlackBoardKey);

	if (!target && patrolPoint.IsZero())
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	const auto forwardVector = actor->GetActorForwardVector();
	FVector directionToTarget = { };
	if (target)
		directionToTarget = (target->GetActorLocation() - actor->GetActorLocation()).GetSafeNormal();
	else
		directionToTarget = (patrolPoint - actor->GetActorLocation()).GetSafeNormal();

	const auto product = FVector::CrossProduct(forwardVector, directionToTarget);

	const float angle = FMath::RadiansToDegrees(product.Size() * FMath::Sign(product.Z));
	const float allowableError = 5.0f;
	if (angle < allowableError)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	const float rotationSpeed = 360.0f * 100;
	FRotator NewRotation = FRotator(0, FMath::Min(angle, FMath::DegreesToRadians(rotationSpeed * DeltaSeconds)), 0);
	FQuat QuatRotation = FQuat(NewRotation);
	actor->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}
