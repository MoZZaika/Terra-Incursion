// Fill out your copyright notice in the Description page of Project Settings.

#include "Team/Team.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATeam::ATeam()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	int slotIndex = 0;
	for (auto& it : warriors)
	{
		FString componentName = TEXT("Slot_") + FString::FromInt(slotIndex);

		auto newSlot = CreateDefaultSubobject<USceneComponent>(static_cast<FName>(componentName));

		if (newSlot == nullptr)
			return;

		slots.Add(newSlot);

		newSlot->SetAutoActivate(true);
		newSlot->SetMobility(EComponentMobility::Movable);
		newSlot->AttachTo(GetRootComponent());

		it.slot = newSlot;

		++slotIndex;
	}
}


// Called when the game starts or when spawned
void ATeam::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	if (world == nullptr)
		return;

	FActorSpawnParameters spawnParams = { };
	spawnParams.bNoFail = true;

	for (auto& warrior : warriors)
	{
		if (warrior.warriorClass == nullptr)
			break;

		auto transform = warrior.slot->GetComponentTransform();

		ACharacter* newActor = dynamic_cast<ACharacter*>(world->SpawnActor(warrior.warriorClass, &transform, spawnParams));
		newActor->SpawnDefaultController();

		if (newActor == nullptr)
			break;

		warrior.instance = dynamic_cast<ACharacter*>(newActor);
		warrior.controller = dynamic_cast<AAIController*>(newActor->GetController());
	}

	UCameraComponent* camera = dynamic_cast<UCameraComponent*>(GetComponentByClass(UCameraComponent::StaticClass()));

	if (camera == nullptr)
		return;

	camera->Activate(true);
}


void ATeam::MoveLeftRight(const float axisValue)
{
	moveDirection.Y = axisValue;
}


void ATeam::MoveForwardBack(const float axisValue)
{
	moveDirection.X = axisValue;
}


// Called every frame
void ATeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->AddMovementInput(moveDirection, movmentSpeed);

	for (auto& warrior : warriors)
	{
		if (warrior.controller == nullptr)
			break;

		warrior.controller->MoveToLocation(warrior.slot->GetComponentLocation());
	}

}

// Called to bind functionality to input
void ATeam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ATeam::MoveLeftRight);
	PlayerInputComponent->BindAxis("MoveForwardBack", this, &ATeam::MoveForwardBack);

}

