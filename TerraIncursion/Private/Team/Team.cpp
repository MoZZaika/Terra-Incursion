#include "Team/Team.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Enemy/HealthComponent.h"
#include "Enemy/BaseEnemyCharacter.h"
#include <Miscs/Utilities.h>
#include "CollisionDebugDrawingPublic.h"
#include "Camera/CameraComponent.h"

ATeam::ATeam()
{
	PrimaryActorTick.bCanEverTick = true;

	mainSlot = CreateDefaultSubobject<USceneComponent>("MainSlot");
	CHECK_ERROR(mainSlot, TEXT("mainSlot is nullptr!"));
	mainSlot->SetAutoActivate(true);
	mainSlot->SetMobility(EComponentMobility::Movable);
	mainSlot->SetupAttachment(GetRootComponent());

	uint32 slotIndex = 0;
	const FString slotNamePrefix = TEXT("Slot_");
	const FString weaponNamePrefix = TEXT("Weapon_");
	
	for (auto& warrior : warriors)
	{
		const FString componentName = slotNamePrefix + FString::FromInt(slotIndex);

		const auto newSlot = CreateDefaultSubobject<USceneComponent>(static_cast<FName>(componentName));
		CHECK_ERROR(newSlot, TEXT("newSlot is nullptr!"));
		slots.Add(newSlot);

		newSlot->SetAutoActivate(true);
		newSlot->SetMobility(EComponentMobility::Movable);
		newSlot->SetupAttachment(mainSlot);

		warrior.slot = newSlot;

		++slotIndex;
		

	}
}


void ATeam::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const world = GetWorld();
	CHECK_ERROR(world, "world is nullptr!");

	FActorSpawnParameters spawnParams = { };
	spawnParams.bNoFail = true;
	UClass* weaponComponentClass = UWeaponComponent::StaticClass();

	for (auto& warrior : warriors)
	{
		CHECK_ERROR(warrior.warriorClass, TEXT("warrior.warriorClass is nullptr!"));
		CHECK_ERROR(warrior.slot, TEXT("warrior.slot is nullptr!"));
		
		const auto transform = warrior.slot->GetComponentTransform();

		ACharacter* const newWarriorInstance = Cast<ACharacter>(world->SpawnActor(warrior.warriorClass, &transform, spawnParams));
		CHECK_ERROR(newWarriorInstance, TEXT("newWarriorInstance is nullptr!"));

		newWarriorInstance->SpawnDefaultController();

		warrior.instance = Cast<ACharacter>(newWarriorInstance);

		warrior.controller = Cast<AAIController>(newWarriorInstance->GetController());

		warrior.weaponComponent = Cast<UWeaponComponent>(newWarriorInstance->GetComponentByClass(weaponComponentClass));
		CHECK_ERROR(warrior.weaponComponent, TEXT("weaponComponent is nullptr"));

		warrior.retreatmentTimerHandle = new FTimerHandle();

	}
}


void ATeam::MoveLeftRight(const float axisValue)
{
	moveDirection.Y = axisValue;
}


void ATeam::MoveForwardBack(const float axisValue)
{
	moveDirection.X = axisValue;
}

void ATeam::AttackLeft()
{
	if(IsValid(warriors[1].instance))
		WarriorMoveToAttack(warriors[1]);
}

void ATeam::AttackRight()
{
	if (IsValid(warriors[2].instance))
		WarriorMoveToAttack(warriors[2]);
}

void ATeam::AttackForward()
{
	if (IsValid(warriors[0].instance))
		WarriorMoveToAttack(warriors[0]);
}

void ATeam::SpawnHealItem()
{
	auto world = GetWorld();
	
	if (!world || healItemReloadTimer > 0)
		return;
	
	world->SpawnActor(healItem, &mainSlot->GetComponentTransform());
	healItemReloadTimer = healItemReload;
}

void ATeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CHECK_ERROR(mainSlot, "mainSlot is nullptr!");

	AddMovementInput(moveDirection, teamMovmentSpeed);

	healItemReloadTimer -= FMath::Min(DeltaTime, healItemReloadTimer);

	if (healItemReloadTimer < 0)
		healItemReloadTimer = 0;

	FCollisionQueryParams collisionQueryParams = { };

	for (auto& warrior : warriors)
	{
		if(warrior.instance)
			collisionQueryParams.AddIgnoredActor(warrior.instance);
	}

	bool dead = true;

	for (auto& warrior : warriors)
	{
		dead = !IsValid(warrior.instance);
		if (!dead)
			break;
	}

	if (dead)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}

	for (auto& warrior : warriors)
	{
		auto& warriorInstance = warrior.instance;
		auto& warriorSlot = warrior.slot;
		auto& warriorController = warrior.controller;
		auto& currentTarget = warrior.currentTarget;

		if (warriorController == nullptr)
			continue;

		if (warriorInstance == nullptr)
			continue;

		if (warriorSlot == nullptr)
			continue;

		if (warriorInstance->IsPendingKillPending()) {
			continue;
		}

		if (currentTarget != nullptr) {

			const float DistanceToTarget = (currentTarget->GetActorLocation() - warriorInstance->GetActorLocation()).Size();
			if (DistanceToTarget <= warrior.weaponComponent->GetWeaponAttackDistance())
			{
				WarriorAttack(warrior);
			}
			continue;
		}

		if (warrior.canRunToSlot == false) {
			continue;
		}


		FHitResult outHit = { };
		const bool hitResult = GetWorld()->LineTraceSingleByChannel(outHit, warriorInstance->GetActorLocation(), warriorSlot->GetComponentLocation(),
			ECC_Visibility, collisionQueryParams);

		if (hitResult)
		{
			warriorController->MoveToLocation(slots[0]->GetComponentLocation());
		}
		else
		{
			warriorController->MoveToLocation(warriorSlot->GetComponentLocation());
		}

		warriorInstance->SetActorRotation(mainSlot->GetComponentRotation());
		
		if (warrior.currentTarget && warrior.currentTarget->IsPendingKill())
		{
			warrior.currentTarget = nullptr;
			warrior.canRunToSlot = true;
		}

	}

	auto const playerController = Cast<APlayerController>(GetController());
	CHECK_ERROR(playerController, TEXT("playerController is nullptr!"));

	FVector mousePosition;
	FVector mouseDirection;
	if (!playerController->DeprojectMousePositionToWorld(mousePosition, mouseDirection))
		return;

	FVector position = mainSlot->GetComponentLocation();

	const float mouseTraceDistance = FMath::Sqrt(FMath::Pow(FMath::Abs(mousePosition.Z - position.Z), 2)
		+ FMath::Pow(FMath::Abs(mousePosition.Y - position.Y), 2)) * 2;

	mousePosition += mouseDirection * mouseTraceDistance;

	position.Z = 0;
	mousePosition.Z = 0;

	FVector viewDirection = mousePosition - position;
	viewDirection.Normalize();

	const auto crossVector = FVector::CrossProduct(mainSlot->GetForwardVector(), viewDirection);
	const float crossValue = crossVector.Size();
	float angle = FMath::RadiansToDegrees(FMath::Asin(crossValue));
	
	const float sensitivity = 0.0001;

	if (FMath::Abs(angle) <= sensitivity)
		return;

	angle *= FMath::Sign(crossVector.Z);
	angle /= 100.0f;

	const auto rotator = GetTransform().Rotator().Add(0, angle * DeltaTime * 1000, 0);
	mainSlot->AddWorldRotation(rotator);

}

void ATeam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	CHECK_ERROR(PlayerInputComponent, "PlayerInputComponent is null!");

	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ATeam::MoveLeftRight);
	PlayerInputComponent->BindAxis("MoveForwardBack", this, &ATeam::MoveForwardBack);

	PlayerInputComponent->BindAction("AttackLeft", IE_Pressed, this, &ATeam::AttackLeft);
	PlayerInputComponent->BindAction("AttackRight", IE_Pressed, this, &ATeam::AttackRight);
	PlayerInputComponent->BindAction("AttackForward", IE_Pressed, this, &ATeam::AttackForward);
	PlayerInputComponent->BindAction("SpawnHeal", IE_Pressed, this, &ATeam::SpawnHealItem);

}

void ATeam::FindTarget(FWarriorData& warrior)
{
	TArray<AActor*> FoundedActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseEnemyCharacter::StaticClass(), FoundedActors);

	if (FoundedActors.Num() == 0)
	{
		return;
	}


	const auto WarriorController = Cast<AAIController>(warrior.controller);
	if (!WarriorController) return;

	const auto Pawn = WarriorController->GetPawn();
	if (!Pawn) return;


    float BestDistance = warrior.lockTargetDistance;
	AActor* BestTarget = nullptr;
	FCollisionQueryParams collisionQueryParams = { };
	
	for (auto& warrior : warriors) {
		collisionQueryParams.AddIgnoredActor(warrior.instance);
	}
	collisionQueryParams.AddIgnoredActor(this);

	for (const auto FoundedActor : FoundedActors)
	{
		if (!FoundedActor->GetClass()->IsChildOf(ABaseEnemyCharacter::StaticClass()))
		{
			continue;
		};

		const auto HealthComponent = Cast<UHealthComponent>(FoundedActor->GetComponentByClass(UHealthComponent::StaticClass()));


		if (!HealthComponent || HealthComponent->IsDead())
		{
			continue;
		}

		const auto CurrentDistance = (FoundedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
		if (CurrentDistance < BestDistance)
		{
			collisionQueryParams.AddIgnoredActor(FoundedActor);
			FHitResult outHit = { };
			const bool hitResult = GetWorld()->LineTraceSingleByChannel(outHit, Pawn->GetActorLocation(), FoundedActor->GetActorLocation(),
				ECC_Visibility, collisionQueryParams);

			if (hitResult) {
				continue;
			}
			BestDistance = CurrentDistance;
			BestTarget = FoundedActor;
		}
		
	}

	warrior.currentTarget = BestTarget;

}

void ATeam::WarriorMoveToAttack(FWarriorData& warrior)
{
	if (warrior.instance->IsPendingKillPending()) {
		return;
	}

	const float offset = 200.0f;
	FindTarget(warrior);
	AActor* currentTarget = warrior.currentTarget;
	if (currentTarget) {
		warrior.controller->MoveToActor(currentTarget, warrior.weaponComponent->GetWeaponAttackDistance() - offset);
	}
	
}

void ATeam::WarriorAttack(FWarriorData& warrior)
{
	if (!warrior.weaponComponent->IsAttackEnabled()) {
		return;
	}

	warrior.canRunToSlot = false;

	FRotator rotationTowardsTarget = (warrior.currentTarget->GetActorLocation() - warrior.instance->GetActorLocation()).Rotation();
	warrior.instance->SetActorRotation(rotationTowardsTarget,ETeleportType::None);
	
	warrior.currentTarget = nullptr;

	CHECK_ERROR(warrior.weaponComponent, TEXT("weaponComponent is nullptr"))
	warrior.weaponComponent->StartAttack();

	GetWorld()->GetTimerManager().SetTimer(*warrior.retreatmentTimerHandle, [&]()
		{
			warrior.canRunToSlot = true;
		}, warriorsRetreatDelay, false);

}
