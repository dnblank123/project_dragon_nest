#include "Modes/CDragonAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CDragonStateComponent.h"

ACDragonAction::ACDragonAction()
{
}

void ACDragonAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	State = CHelpers::GetComponentFromActor<UCDragonStateComponent>(OwnerCharacter);
	Attack = CHelpers::GetComponentFromActor<UCDragonAttackComponent>(OwnerCharacter);

	Super::BeginPlay();
}

