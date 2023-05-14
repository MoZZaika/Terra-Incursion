// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "AttackPositionEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINCURSION_API UAttackPositionEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Meta")
	FName enemyActorKey = "Player";
};
