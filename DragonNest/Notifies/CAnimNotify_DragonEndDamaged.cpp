#include "Notifies/CAnimNotify_DragonEndDamaged.h"
#include "Global.h"
#include "Characters/CDragon.h"

FString UCAnimNotify_DragonEndDamaged::GetNotifyName_Implementation() const
{
	return "DragonEndDamaged";
}

void UCAnimNotify_DragonEndDamaged::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	ACDragon* dragon = Cast<ACDragon>(MeshComp->GetOwner());
	MustNotNull(dragon);

	dragon->SetIdleAfterDamaged();
	dragon->bAlreadySetDamagedDirection = false;
}
