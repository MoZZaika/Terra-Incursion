// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/HealthComponent.h"
#include "Miscs/Utilities.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	CHECK_ERROR(ComponentOwner, "HealthComponent Owner is nullptr");

	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	ApplyDamage(Damage,InstigatedBy);
}

void UHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - HealthValue;

	HealthValue = NextHealth;
	OnHealthChanged.Broadcast(HealthValue, HealthDelta);
}

void UHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	const auto World = GetWorld();
	CHECK_ERROR(World, "World is nullptr");

	if (IsDead()) return;

	SetHealth(HealthValue - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}



