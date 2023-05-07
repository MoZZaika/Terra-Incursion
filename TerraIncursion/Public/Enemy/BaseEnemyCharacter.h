
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h" 
#include "BaseEnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class FAttackType : uint8
{
	MEAL UMETA(DisplayName = "Meal")
};

UCLASS()
class TERRAINCURSION_API ABaseEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UHealthComponent* HealthComponent;

public:

	ABaseEnemyCharacter();

	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	virtual void Attack(ACharacter* target, const FAttackType attackType);

protected:

	UPROPERTY(EditDefaultsOnly)
	float movementSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	float detectionRange = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float MealAttackDamage = 5.0f;

	virtual void OnDeath();
	virtual void OnHealthChanged(float Health, float HealthDelta);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
