#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONNEST_API UCOptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCOptionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float SlowMoveSpeed = 100.0f;
	float NormalMoveSpeed = 300.0f;
	float DashMoveSpeed = 800.0f;

	float MouseRate = 45.0f;
	float JumpPower = 500.0f;
	float AirControl = 0.7f;

	float damageMultiplyValue = 100.0f;

public:
	FORCEINLINE float GetSlowMoveSpeed() { return SlowMoveSpeed; }
	FORCEINLINE float GetNormalMoveSpeed() { return NormalMoveSpeed; }
	FORCEINLINE float GetDashMoveSpeed() { return DashMoveSpeed; }

	FORCEINLINE float GetMouseRate() { return MouseRate; }
	FORCEINLINE float GetJumpPower() { return JumpPower; }
	FORCEINLINE float GetAirControl() { return AirControl; }

	FORCEINLINE float GetDamageMultiplyValue() { return damageMultiplyValue; }
};
