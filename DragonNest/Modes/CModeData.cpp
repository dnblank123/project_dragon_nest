#include "Modes/CModeData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Modes/CAttachment.h"
#include "Modes/CEquipment.h"
#include "Modes/CAction.h"



void UCModeData::BeginPlay(class ACharacter* InOwnerCharacter)
{
	FTransform transform;
	
	if (!!AttachmentClass)
	{
		AttachmentActor = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		AttachmentActor->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

		UGameplayStatics::FinishSpawningActor(AttachmentActor, transform);
	}

	if (!!EquipmentClass)
	{
		EquipmentActor = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOwnerCharacter);
		EquipmentActor->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		EquipmentActor->SetEquipmentData(EquipmentData);

		UGameplayStatics::FinishSpawningActor(EquipmentActor, transform);

		if (!!AttachmentClass)
		{
			EquipmentActor->OnEquip.AddDynamic(AttachmentActor, &ACAttachment::OnEquip);
			EquipmentActor->OnUnequipFinished.AddDynamic(AttachmentActor, &ACAttachment::OnUnequipFinished);
			//EquipmentActor->OnUnequipFinished.AddDynamic(Mode, &ACAttachment::OnUnequipFinished);
		}
	}

	if (!!ActionClass)
	{
		ActionActor = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAction>(ActionClass, transform, InOwnerCharacter);
		ActionActor->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		ActionActor->SetComboDatas(ComboActionDatas);

		UGameplayStatics::FinishSpawningActor(ActionActor, transform);

		if (!!EquipmentActor)
		{
			//ActionActor->SetEquipped(Equipment->GetEquipped());
		}

		if (!!AttachmentActor)
		{
			AttachmentActor->OnAttachmentBeginOverlapDelegate.AddDynamic(ActionActor, &ACAction::OnAttachmentBeginOverlap);
			AttachmentActor->OnAttachmentEndOverlapDelegate.AddDynamic(ActionActor, &ACAction::OnAttachmentEndOverlap);

			AttachmentActor->OnAttachmentCollisionDelegate.AddDynamic(ActionActor, &ACAction::OnAttachmentCollision);
			AttachmentActor->OffAttachmentCollisionDelegate.AddDynamic(ActionActor, &ACAction::OffAttachmentCollision);
		}
	}

}