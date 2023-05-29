// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/BaseEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Enemy/HealthComponent.h"
#include "Components/CapsuleComponent.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEnemyCharacter::Attack(ACharacter* target, const FAttackType attackType)
{
	if (!target)
		return;

	float dmg = 0;

	switch (attackType)
	{
	case FAttackType::MELEE:
		dmg = MealAttackDamage;
		break;
	case FAttackType::RANGE:
		GetWorld()->SpawnActor(projectileClass, &GetActorTransform());
		break;
	default:
		break;
	}

	if(attackType != FAttackType::RANGE)
		target->TakeDamage(dmg, FDamageEvent(), GetController(), this);
}

bool ABaseEnemyCharacter::GetRangedAttack() const
{
	return RangedAttack;
}

float ABaseEnemyCharacter::GetRangedAttackDistance() const
{
	return RangedAttackDistance;
}

void ABaseEnemyCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	auto controller = GetController();
	controller->UnPossess();
	controller->Destroy();
}

void ABaseEnemyCharacter::OnHealthChanged(float Health, float HealthDelta)
{
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetCapsuleComponent());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ABaseEnemyCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ABaseEnemyCharacter::OnHealthChanged);
}

void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

