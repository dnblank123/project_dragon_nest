#include "Components/CDragonAttackComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Modes/CDragonAction.h"

UCDragonAttackComponent::UCDragonAttackComponent()
{
}

void UCDragonAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	InitData();
}

void UCDragonAttackComponent::InitData()
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	MustNotNull(character);

	AttackData->BeginPlay(character);
}

void UCDragonAttackComponent::DoAction(EDragonAttackType InNewAction)
{
	ChangeAttackType(InNewAction);

	AttackData->GetDoActionActor()->DoAction(InNewAction);
}

void UCDragonAttackComponent::ChangeAttackType(EDragonAttackType InNewAction)
{
	EDragonAttackType PrevMode = CurAttackType;
	CurAttackType = InNewAction;
}

void UCDragonAttackComponent::EnableCollision()
{
	TArray<EDragonAttachmentType> AttachmentsToActive = AttackData->GetAttackData(CurAttackType).AttachmentsToActive;
	for (int32 i = 0; i < AttachmentsToActive.Num(); i++)
		AttackData->GetAttachmentActor()->TurnOnDragonCollision(AttachmentsToActive[i]);
}

