#include "Components/CStateComponent.h"
#include "Global.h"

UCStateComponent::UCStateComponent()
{
}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIdleState();	
}

void UCStateComponent::ChangeState(EStateType InState)
{
	EStateType PrevState = CurState;
	CurState = InState;

	if (OnStateChanged.IsBound()) OnStateChanged.Broadcast(PrevState, CurState);
}

void UCStateComponent::SetIdleState()
{
	ChangeState(EStateType::Idle);
}

void UCStateComponent::SetEquipState()
{
	ChangeState(EStateType::Equip);
}

void UCStateComponent::SetRollState(EStateType type)
{
	ChangeState(type);
}	

void UCStateComponent::SetDashState()
{
	ChangeState(EStateType::Dash);
}

void UCStateComponent::SetAttackState()
{
	ChangeState(EStateType::Attack);
}

void UCStateComponent::SetDamagedState()
{
	ChangeState(EStateType::Damaged);
}

void UCStateComponent::SetDeadState()
{
	ChangeState(EStateType::Dead);
}
