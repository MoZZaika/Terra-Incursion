// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FindEnemyService.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Team/Team.h"

UFindEnemyService::UFindEnemyService()
{
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto blackBoard = OwnerComp.GetBlackboardComponent();

	if (!blackBoard)
		return;

	const auto controller = OwnerComp.GetAIOwner();

	if (!controller)
		return;

	const auto perceptionComponent = Cast<AEnemyAIController>(controller)->GetPerceptionComponent();

	if (!perceptionComponent)
		return;

	blackBoard->SetValueAsObject(playerBlackBoardKey, nullptr);

	TArray<AActor*> percrvieActors { };
	perceptionComponent->GetCurrentlyPerceivedActors(ATeam::StaticClass(), percrvieActors);

	for (auto it : percrvieActors)
	{
		blackBoard->SetValueAsObject(playerBlackBoardKey, it);
	}
}
