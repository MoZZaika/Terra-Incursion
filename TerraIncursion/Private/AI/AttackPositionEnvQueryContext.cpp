// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AttackPositionEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void UAttackPositionEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto queryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	const auto blackboard = UAIBlueprintHelperLibrary::GetBlackboard(queryOwner);
	if (!blackboard)
		return;

	const auto target = blackboard->GetValueAsObject(enemyActorKey);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(target));
}
