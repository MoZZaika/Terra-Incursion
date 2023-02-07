// Fill out your copyright notice in the Description page of Project Settings.

#include "Team/Team.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATeam::ATeam()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	mainSlot = CreateDefaultSubobject<USceneComponent>("MainSlot");
	mainSlot->SetAutoActivate(true);
	mainSlot->SetMobility(EComponentMobility::Movable);
	mainSlot->AttachTo(GetRootComponent());

	if (mainSlot == nullptr)
		return;

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
		newSlot->AttachToComponent(mainSlot, FAttachmentTransformRules::SnapToTargetIncludingScale);

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
		warrior.instance->SetActorRotation(mainSlot->GetComponentRotation());
	}

	auto playerController = dynamic_cast<APlayerController*>(GetController());

	if (playerController == nullptr)
		return;

	FVector mousePosition;
	FVector mouseDirection;

	if (!playerController->DeprojectMousePositionToWorld(mousePosition, mouseDirection))
		return;

	const float mouseTraceDistance = -mousePosition.Z / mouseDirection.Z;

	mousePosition += mouseDirection * mouseTraceDistance;

	FVector position = mainSlot->GetComponentLocation();
	position.Z = 0;

	FVector viewDirection = mousePosition - position;
	viewDirection.Normalize();

	auto c = FVector::CrossProduct(mainSlot->GetForwardVector(), viewDirection);
	const float dotValue = c.Size();
	float angle = FMath::RadiansToDegrees(FMath::Asin(dotValue));
	
	if (c.Z < 0)
		angle *= -1;
	
	const float eps = 0.00001;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, c.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::SanitizeFloat(a2, 3));


		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, mousePosition.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, position.ToString());

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, GetActorForwardVector().ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, viewDirection.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::SanitizeFloat(angle, 3));
	}


	if (FMath::Abs(angle) <= eps)
		return;

	auto rotator = GetTransform().Rotator().Add(0, angle, 0);
	mainSlot->AddWorldRotation(rotator);

}

// Called to bind functionality to input
void ATeam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ATeam::MoveLeftRight);
	PlayerInputComponent->BindAxis("MoveForwardBack", this, &ATeam::MoveForwardBack);

}

