#include "Characters/CDragonAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CDragon.h"

void UCDragonAnimInstance::NativeBeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	Dragon = Cast<ACDragon>(OwnerCharacter);

	Super::NativeBeginPlay();
}

void UCDragonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	MustNotNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation()); 

	bIsJumping = false;

	CurStateType = Dragon->GetCurState();
}
