// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyAIController::AEnemyAIController()
{
	perception = CreateDefaultSubobject<UAIPerceptionComponent>("CreateDefaultSubobject");
	SetPerceptionComponent(*perception);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn)
		return;

	if (!behaviorTree)
		return;

	RunBehaviorTree(behaviorTree);
}
