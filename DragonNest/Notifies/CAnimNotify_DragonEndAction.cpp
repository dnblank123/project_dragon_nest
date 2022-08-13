#include "Notifies/CAnimNotify_DragonEndAction.h"
#include "Global.h"
#include "Components/CDragonAttackComponent.h"
#include "Modes/CDragonAttackData.h"
#include "Modes/CDragonAction.h"

FString UCAnimNotify_DragonEndAction::GetNotifyName_Implementation() const
{
	return "DragonEndAction";
}

void UCAnimNotify_DragonEndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	UCDragonAttackComponent* attack = CHelpers::GetComponentFromActor<UCDragonAttackComponent>(MeshComp->GetOwner());

	MustNotNull(attack);
	MustNotNull(attack->GetAttackData());
	MustNotNull(attack->GetAttackData()->GetDoActionActor());

	attack->GetAttackData()->GetDoActionActor()->EndAnimation_Action();
}
