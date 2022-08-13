#include "CAnimNotify_EndAction.h"
#include "Global.h"
#include "Components/CModeComponent.h"
#include "Modes/CModeData.h"
#include "Modes/CAction.h"

FString UCAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UCAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	UCModeComponent* mode = CHelpers::GetComponentFromActor<UCModeComponent>(MeshComp->GetOwner());

	MustNotNull(mode);
	MustNotNull(mode->GetCurrent());
	MustNotNull(mode->GetCurrent()->GetActionActor());

	mode->GetCurrent()->GetActionActor()->EndAnimation_Action(); 
}
