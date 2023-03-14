// Fill out your copyright notice in the Description page of Project Settings.


#include "SpearWeapon.h"

// Sets default values
ASpearWeapon::ASpearWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpearWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpearWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpearWeapon::StartAttack() {
	ABaseWeapon::StartAttack();

}

