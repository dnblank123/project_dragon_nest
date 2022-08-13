#include "Notifies/CAnimNotifyState_EnableCombo.h"
#include "Global.h"
#include "Components/CModeComponent.h"
#include "Modes/CModeData.h"
#include "Modes/CAction.h"
#include "Modes/CAction_Melee.h"

FString UCAnimNotifyState_EnableCombo::GetNotifyName_Implementation() const
{
	return "EnableCombo";
}

void UCAnimNotifyState_EnableCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());
	
	UCModeComponent* mode = CHelpers::GetComponentFromActor<UCModeComponent>(MeshComp->GetOwner());

	MustNotNull(mode);
	MustNotNull(mode->GetCurrent());
	MustNotNull(mode->GetCurrent()->GetActionActor());
	
	ACAction_Melee* melee = Cast<ACAction_Melee>(mode->GetCurrent()->GetActionActor());
	MustNotNull(melee);

	melee->EnableCombo();
}

void UCAnimNotifyState_EnableCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	UCModeComponent* mode = CHelpers::GetComponentFromActor<UCModeComponent>(MeshComp->GetOwner());

	MustNotNull(mode);
	MustNotNull(mode->GetCurrent());
	MustNotNull(mode->GetCurrent()->GetActionActor());

	ACAction_Melee* melee = Cast<ACAction_Melee>(mode->GetCurrent()->GetActionActor());
	MustNotNull(melee);

	melee->DisableCombo();
}
