#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDragonStateComponent.generated.h"

UENUM(BlueprintType)
enum class EDragonStateType : uint8 
{
	Idle,
	Attack,
	Damaged,
	Dead,
	Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDragonStateChangedDelegate, EDragonStateType, InPrevState, EDragonStateType, InNewState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONNEST_API UCDragonStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCDragonStateComponent();

protected:
	virtual void BeginPlay() override;

private:
	EDragonStateType CurState;

public:
	UPROPERTY(BlueprintAssignable)
		FDragonStateChangedDelegate OnStateChanged;

private:
	void ChangeState(EDragonStateType InState);

public:
	FORCEINLINE EDragonStateType GetCurState() { return CurState; }
	FORCEINLINE bool IsIdle() { return (CurState == EDragonStateType::Idle); }
	FORCEINLINE bool IsAttacking() { return (CurState == EDragonStateType::Attack); }
	FORCEINLINE bool IsDamaged() { return (CurState == EDragonStateType::Damaged); }
	FORCEINLINE bool IsDead() { return (CurState == EDragonStateType::Dead); }

	void SetIdleState();
	void SetAttackState();
	void SetDamagedState();
	void SetDeadState();


};
