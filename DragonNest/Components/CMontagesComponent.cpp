#include "Components/CMontagesComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCMontagesComponent::UCMontagesComponent()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();
	
	MustNotNull(MontageDataTable);

	TArray<FMontageData*> datas;
	MontageDataTable->GetAllRows<FMontageData>("", datas);
	
	for (int32 i = 0; i < (int32)EStateType::Max; i++)
		for (FMontageData* data : datas)
			if (data->Type == (EStateType)i) MontageData[i] = data;
}

void UCMontagesComponent::PlayMontage()
{
	const FMontageData* data = MontageData[(int32)State];

	if (!!data && !!data->AnimMontage)
	{
		if (State == EStateType::Dead) data->AnimMontage->SequenceLength = MAX_FLT;
		OwnerCharacter->PlayAnimMontage(data->AnimMontage, data->PlayerRatio, data->StartSection);
	}
}

void UCMontagesComponent::PlayEquip()
{
	State = EStateType::Equip;
	PlayMontage();
}

void UCMontagesComponent::PlayRoll(EStateType type)
{
	State = type;
	PlayMontage();
}

void UCMontagesComponent::PlayDamaged()
{
	State = EStateType::Damaged;
	PlayMontage();
}

void UCMontagesComponent::PlayDead()
{
	State = EStateType::Dead;
	PlayMontage();
}

void UCMontagesComponent::StopCurMontage()
{
	OwnerCharacter->StopAnimMontage(MontageData[(int32)State]->AnimMontage);
}


