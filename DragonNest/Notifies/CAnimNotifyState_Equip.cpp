#include "Notifies/CAnimNotifyState_Equip.h"
#include "Global.h"
#include "Components/CModeComponent.h"
#include "Modes/CEquipment.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());
	UCModeComponent* mode = CHelpers::GetComponentFromActor<UCModeComponent>(MeshComp->GetOwner());
	MustNotNull(mode);

	mode->GetCurrent()->GetEquipmentActor()->BeginAnimation_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());
	UCModeComponent* mode = CHelpers::GetComponentFromActor<UCModeComponent>(MeshComp->GetOwner());
	MustNotNull(mode);

	mode->GetCurrent()->GetEquipmentActor()->EndAnimation_Equip();

	if (mode->GetCurrent()->GetEquipmentActor()->IsUnequipState()) mode->ChangeModeToUnarmed();
}
