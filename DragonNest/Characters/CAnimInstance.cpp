#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CPlayer.h"

void UCAnimInstance::NativeBeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	Player = Cast<ACPlayer>(OwnerCharacter);

	MustNotNull(OwnerCharacter);
	UCModeComponent* mode = CHelpers::GetComponentFromActor<UCModeComponent>(OwnerCharacter);
	MustNotNull(mode);
	mode->OnModeChanged.AddDynamic(this, &UCAnimInstance::OnModeChanged);

	Super::NativeBeginPlay();
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	MustNotNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
	
	bIsJumping = Player->bIsJumping;
	bIsWalking = Player->bIsWalkKeyBeingPressed;

	CurStateType = Player->GetCurState();
}

void UCAnimInstance::OnModeChanged(EModeType InPrevMode, EModeType InNewMode)
{
	CurModeType = InNewMode;
}
