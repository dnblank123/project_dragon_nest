#include "Notifies/CAnimNotify_EndDamaged.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/CStatusComponent.h"

FString UCAnimNotify_EndDamaged::GetNotifyName_Implementation() const
{
	return "EndDamaged";
}

void UCAnimNotify_EndDamaged::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	UCStatusComponent* status = CHelpers::GetComponentFromActor<UCStatusComponent>(MeshComp->GetOwner());
	UCStateComponent* state = CHelpers::GetComponentFromActor<UCStateComponent>(MeshComp->GetOwner());

	MustNotNull(status);
	MustNotNull(state);

	status->SetCanMove();
	state->SetIdleState();
}
