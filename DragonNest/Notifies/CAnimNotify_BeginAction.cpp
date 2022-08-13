#include "CAnimNotify_BeginAction.h"
#include "Global.h"
#include "Components/CModeComponent.h"
#include "Modes/CModeData.h"
#include "Modes/CAction.h"

FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "BeginAction";	
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	UCModeComponent* mode = CHelpers::GetComponentFromActor<UCModeComponent>(MeshComp->GetOwner());

	MustNotNull(mode);
	MustNotNull(mode->GetCurrent());
	MustNotNull(mode->GetCurrent()->GetActionActor());

	mode->GetCurrent()->GetActionActor()->BeginAnimation_Action();
}
