// Fill out your copyright notice in the Description page of Project Settings.


#include "Team/Warrior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/HealthComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AWarrior::AWarrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	healthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	healthComponent->OnDeath.AddUObject(this, &AWarrior::OnDeath);

	Tags.Add("Team");
}

// Called when the game starts or when spawned
void AWarrior::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWarrior::OnDeath()
{
	Tags.Remove("Team");

	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

