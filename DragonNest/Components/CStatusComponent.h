#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONNEST_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

private:
	bool bCanMove;
	bool bIsInvincible;
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		float MaxHealth = 100.0f;

public:
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }

	FORCEINLINE bool CanMove() { return bCanMove; }
	FORCEINLINE bool IsInvincible() { return bIsInvincible; }

	FORCEINLINE void SetCanMove() { bCanMove = true; }
	FORCEINLINE void SetStop() { bCanMove = false; }
	FORCEINLINE void SetInvincible() { bIsInvincible = true; }
	FORCEINLINE void SetCanBeAttacked() { bIsInvincible = false; }

	void AddHealth(float InAmount);
	void SubHealth(float InAmount);

};
