#include "Notifies/CAnimNotify_BeginDash.h"
#include "Global.h"
#include "Components/AudioComponent.h"

FString UCAnimNotify_BeginDash::GetNotifyName_Implementation() const
{
	return "BeginDash";
}

void UCAnimNotify_BeginDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	UAudioComponent* audio = CHelpers::GetComponentFromActor<UAudioComponent>(MeshComp->GetOwner());

	MustNotNull(audio);

	audio->Play();
}
