#include "Notifies/CAnimNotifyState_EndJump.h"
#include "Global.h"
#include "Characters/CPlayer.h"


FString UCAnimNotifyState_EndJump::GetNotifyName_Implementation() const
{
	return "EndJump";
}

void UCAnimNotifyState_EndJump::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());
	
	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	MustNotNull(character);
	ACPlayer* player = Cast<ACPlayer>(character);
	MustNotNull(player);

	player->SetIsJumpEnding(true);
}

void UCAnimNotifyState_EndJump::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	MustNotNull(MeshComp);
	MustNotNull(MeshComp->GetOwner());

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	MustNotNull(character);
	ACPlayer* player = Cast<ACPlayer>(character);
	MustNotNull(player);

	player->SetIsJumpEnding(false);
}
