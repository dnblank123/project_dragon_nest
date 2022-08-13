#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8 
{
	Idle,
	Equip,
	Roll_F,
	Roll_B,
	Roll_R,
	Roll_L,
	Dash,
	Attack,
	Damaged,
	Dead,
	Max
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateChangedDelegate, EStateType, InPrevState, EStateType, InNewState);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONNEST_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;
	
private:
	EStateType CurState;

public:
	UPROPERTY(BlueprintAssignable)
		FStateChangedDelegate OnStateChanged;

private:
	void ChangeState(EStateType InState);

public:
	FORCEINLINE EStateType GetCurState() { return CurState; }
	FORCEINLINE bool IsIdle() { return (CurState == EStateType::Idle); }
	FORCEINLINE bool IsRolling() { return (CurState == EStateType::Roll_F || CurState == EStateType::Roll_B || CurState == EStateType::Roll_R || CurState == EStateType::Roll_L); }
	FORCEINLINE bool IsDashing() { return (CurState == EStateType::Dash); }
	FORCEINLINE bool IsAttacking() { return (CurState == EStateType::Attack); }
	FORCEINLINE bool IsDead() { return (CurState == EStateType::Dead); }
	
	void SetIdleState();
	void SetEquipState();
	void SetRollState(EStateType type);
	void SetDashState();
	void SetAttackState();
	void SetDamagedState();
	void SetDeadState();
};
