#include "Components/CModeComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Modes/CModeData.h"
#include "Modes/CEquipment.h"
#include "Modes/CAction.h"

UCModeComponent::UCModeComponent()
{
}

void UCModeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitDatas();
	SetUnarmed();
}

void UCModeComponent::ChangeMode(EModeType InMode)
{
	EModeType PrevMode = CurMode;
	CurMode = InMode;

	if (OnModeChanged.IsBound())
		OnModeChanged.Broadcast(PrevMode, CurMode);
}

void UCModeComponent::InitDatas()
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EModeType::Max; i++)
	{
		if (!!ModeDatas[i])
			ModeDatas[i]->BeginPlay(character);
	}
}

void UCModeComponent::SetUnarmed()
{
	// using by Two Hand EquipmentActor
	MustNotNull(ModeDatas[(int32)CurMode]);
	ACEquipment* e = ModeDatas[(int32)CurMode]->GetEquipmentActor();
	MustNotNull(e);

	e->Unequip();	
}

void UCModeComponent::SetTwoHand()
{
	// using by Two Hand EquipmentActor
	MustNotNull(ModeDatas[(int32)EModeType::TwoHand]);	
	ACEquipment* e = ModeDatas[(int32)EModeType::TwoHand]->GetEquipmentActor();
	MustNotNull(e);

	e->Equip();

	ChangeMode(EModeType::TwoHand);
}

void UCModeComponent::ChangeModeToUnarmed()
{
	ChangeMode(EModeType::Unarmed);
}

void UCModeComponent::ChangeModeToTwoHand()
{
	ChangeMode(EModeType::TwoHand);
}

void UCModeComponent::DoAction(ESkillName Skill)
{
	MustBeFalse(IsUnarmed());

	if (!!ModeDatas[(int32)CurMode])
	{
		ACAction* action = ModeDatas[(int32)CurMode]->GetActionActor();

		if (!!action) action->DoAction(Skill);
	}
}

void UCModeComponent::QuitAction()
{
	MustBeFalse(IsUnarmed());

	if (!!ModeDatas[(int32)CurMode])
	{
		ACAction* action = ModeDatas[(int32)CurMode]->GetActionActor();

		if (!!action) action->EndAnimation_Action();
	}

}
