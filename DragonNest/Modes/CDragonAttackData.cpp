#include "Modes/CDragonAttackData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Modes/CDragonAttachment.h"
#include "Modes/CDragonAction.h"

void UCDragonAttackData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform transform;

	if (!!AttachmentClass)
	{
		AttachmentActor = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDragonAttachment>(AttachmentClass, transform, InOwnerCharacter);
		AttachmentActor->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

		UGameplayStatics::FinishSpawningActor(AttachmentActor, transform);
	}
	
	if (!!DoActionClass)
	{
		DoActionActor = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDragonAction>(DoActionClass, transform, InOwnerCharacter);
		DoActionActor->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		DoActionActor->SetActionDatas(SingleActionDatas);

		UGameplayStatics::FinishSpawningActor(DoActionActor, transform);

		if (!!AttachmentActor)
		{
			AttachmentActor->OnAttachmentBeginOverlapDelegate.AddDynamic(DoActionActor, &ACDragonAction::OnAttachmentBeginOverlap);
			AttachmentActor->OnAttachmentEndOverlapDelegate.AddDynamic(DoActionActor, &ACDragonAction::OnAttachmentEndOverlap);

			AttachmentActor->OnAttachmentCollisionDelegate.AddDynamic(DoActionActor, &ACDragonAction::OnAttachmentCollision);
			AttachmentActor->OffAttachmentCollisionDelegate.AddDynamic(DoActionActor, &ACDragonAction::OffAttachmentCollision);
		}
	}
}
