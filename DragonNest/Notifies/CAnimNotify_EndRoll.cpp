#include "Notifies/CAnimNotify_EndRoll.h"
#include "Global.h"
#include "Characters/CPlayer.h"

FString UCAnimNotify_EndRoll::GetNotifyName_Implementation() const
{
	return "EndRoll";
}

void UCAnimNotify_EndRoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());
	
	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	MustNotNull(character);
	ACPlayer* player = Cast<ACPlayer>(character);
	MustNotNull(player);
	
	player->CheckEndRollAndBeginDash();
}
