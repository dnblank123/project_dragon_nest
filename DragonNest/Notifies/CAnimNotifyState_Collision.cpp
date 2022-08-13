#include "Notifies/CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Components/CModeComponent.h"
#include "Modes/CAttachment.h"
#include "Modes/CModeData.h"


FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());
	UCModeComponent* mode = CHelpers::GetComponentFromActor<UCModeComponent>(MeshComp->GetOwner());
	MustNotNull(mode);
	ACAttachment* attachment = mode->GetCurrent()->GetAttachmentActor();
	MustNotNull(attachment);

	attachment->TurnOnAllCollision();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	
	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());
	UCModeComponent* mode = CHelpers::GetComponentFromActor<UCModeComponent>(MeshComp->GetOwner());
	MustNotNull(mode);
	ACAttachment* attachment = mode->GetCurrent()->GetAttachmentActor();
	MustNotNull(attachment);

	attachment->TurnOffAllCollision();

	mode->GetCurrent()->GetActionActor()->ResetDamagedCharacters();
}
