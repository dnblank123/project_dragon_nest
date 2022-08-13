#include "Notifies/CAnimNotifyState_DragonCollision.h"
#include "Global.h"
#include "Components/CDragonAttackComponent.h"
#include "Modes/CDragonAttachment.h"

FString UCAnimNotifyState_DragonCollision::GetNotifyName_Implementation() const
{
	return "DragonCollision";
}

void UCAnimNotifyState_DragonCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	UCDragonAttackComponent* attack = CHelpers::GetComponentFromActor<UCDragonAttackComponent>(MeshComp->GetOwner());
	MustNotNull(attack);
	
	attack->EnableCollision();
}

void UCAnimNotifyState_DragonCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	UCDragonAttackComponent* attack = CHelpers::GetComponentFromActor<UCDragonAttackComponent>(MeshComp->GetOwner());
	MustNotNull(attack);

	attack->GetAttachment()->TurnOffAllCollision();
}
