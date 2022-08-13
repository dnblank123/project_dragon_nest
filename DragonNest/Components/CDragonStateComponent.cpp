#include "Components/CDragonStateComponent.h"

UCDragonStateComponent::UCDragonStateComponent()
{
	
}


void UCDragonStateComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIdleState();	
}

void UCDragonStateComponent::ChangeState(EDragonStateType InState)
{
	EDragonStateType PrevState = CurState;
	CurState = InState;

	if (OnStateChanged.IsBound())
		OnStateChanged.Broadcast(PrevState, CurState);
}

void UCDragonStateComponent::SetIdleState()
{
	ChangeState(EDragonStateType::Idle);
}

void UCDragonStateComponent::SetAttackState()
{
	ChangeState(EDragonStateType::Attack);
}

void UCDragonStateComponent::SetDamagedState()
{
	ChangeState(EDragonStateType::Damaged);
}

void UCDragonStateComponent::SetDeadState()
{
	ChangeState(EDragonStateType::Dead);
}

