// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAINCURSION_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(Category = "Health")
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	float GetHealth() const { return Health; }

	UHealthComponent();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (ClampMin = "0.0"))
	float MaxHealth = 100.0f;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Health = 0.0f;

	UFUNCTION()
		void OnTakeAnyDamage(
			AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void SetHealth(float NewHealth);

	void ApplyDamage(float Damage, AController* InstigatedBy);
};
