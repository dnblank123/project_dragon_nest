#include "Modes/CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CStateComponent.h"

ACEquipment::ACEquipment()
{
}

void ACEquipment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponentFromActor<UCStateComponent>(OwnerCharacter);
	
	Super::BeginPlay();
}

void ACEquipment::Equip()
{
	State->SetEquipState();

	EquipStateForAnimation = EEquipState::Equip;

	if (EquipmentData.AnimMontageOnEquip != NULL)
		OwnerCharacter->PlayAnimMontage(EquipmentData.AnimMontageOnEquip, EquipmentData.PlayRatio, EquipmentData.StartSection);
	else EndAnimation_Equip();
}

void ACEquipment::Unequip()
{
	State->SetEquipState();

	EquipStateForAnimation = EEquipState::Unequip;

	if (EquipmentData.AnimMontageOnUnequip != NULL)
		OwnerCharacter->PlayAnimMontage(EquipmentData.AnimMontageOnUnequip, EquipmentData.PlayRatio, EquipmentData.StartSection);
	else EndAnimation_Equip();

}

void ACEquipment::BeginAnimation_Equip()
{
	if (EquipStateForAnimation == EEquipState::Equip)
		if (OnEquip.IsBound()) OnEquip.Broadcast();
}

void ACEquipment::EndAnimation_Equip()
{
	if (EquipStateForAnimation == EEquipState::Unequip)
		if (OnUnequipFinished.IsBound()) OnUnequipFinished.Broadcast();

	State->SetIdleState();
}
