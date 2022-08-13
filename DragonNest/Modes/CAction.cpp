#include "Modes/CAction.h"
#include "Global.h"
#include "Characters/CDragon.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CModeComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/SpringArmComponent.h"


ACAction::ACAction()
{
	CHelpers::CreateComponent<UNiagaraComponent>(this, &Niagara, "Niagara");
}

void ACAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponentFromActor<UCStateComponent>(OwnerCharacter);
	Mode = CHelpers::GetComponentFromActor<UCModeComponent>(OwnerCharacter);

	Super::BeginPlay();
}

void ACAction::SetAndShowNiagaraEffect(FVector Location, FRotator Rotation, int SkillIndex, int ComboIndex)
{
	MustNotNull(Niagara);
	MustNotNull(ComboActionDatas[SkillIndex].SingleActionDatas[ComboIndex].NiagaraSystem);

	Niagara->SetAsset(ComboActionDatas[SkillIndex].SingleActionDatas[ComboIndex].NiagaraSystem);

	Niagara->SetWorldLocation(Location);
	Niagara->SetWorldRotation(Rotation);
	Niagara->ActivateSystem();
}

void ACAction::ResetDamagedCharacters()
{
	DamagedCharacters.Empty();
}