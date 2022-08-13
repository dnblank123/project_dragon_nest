#include "Modes/CDragonAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CDragonStateComponent.h"
#include "CDragonAttackData.h"

void ACDragonAction_Melee::PlayCurAction()
{
}

void ACDragonAction_Melee::DoAction(EDragonAttackType InAttackType)
{
	Super::DoAction(InAttackType);

	FSingleAttackData& data = AttackDatas[(int32)InAttackType];
	OwnerCharacter->PlayAnimMontage(data.AnimMontage, data.PlayRatio, data.StartSection);

	CurAttackType = InAttackType;

	bAlreadyDamaged = false;
}

void ACDragonAction_Melee::BeginAnimation_Action()
{
	Super::BeginAnimation_Action();
}

void ACDragonAction_Melee::EndAnimation_Action()
{
	Super::EndAnimation_Action();

	State->SetIdleState();
	Attack->GetAttackData()->GetAttachmentActor()->TurnOffAllCollision();
}

void ACDragonAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser,	ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);
	
	MustNotNull(InOtherCharacter);
	MustBeFalse(bAlreadyDamaged); // no damage when already damaged

	bAlreadyDamaged = true;

	// give damage
	FDamageEvent e;
	float power = AttackDatas[(int32)CurAttackType].AttackPower;

	float damageBoundary = power * 0.1f;
	power += FMath::FRandRange(-damageBoundary, damageBoundary);

	InOtherCharacter->TakeDamage(power, e, OwnerCharacter->GetController(), this);
}

void ACDragonAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser,	ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InAttackCauser, InOtherCharacter);
}

void ACDragonAction_Melee::OnAttachmentCollision()
{
	Super::OnAttachmentCollision();
}

void ACDragonAction_Melee::OffAttachmentCollision()
{
	Super::OffAttachmentCollision();

	bAlreadyDamaged = false;
}
