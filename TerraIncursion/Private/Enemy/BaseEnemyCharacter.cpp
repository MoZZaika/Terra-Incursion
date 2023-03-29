// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Enemy/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/BaseEnemyCharacter.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEnemyCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
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

