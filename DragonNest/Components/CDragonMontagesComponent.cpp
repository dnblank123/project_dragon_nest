#include "Components/CDragonMontagesComponent.h"

#include "CDragonStateComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCDragonMontagesComponent::UCDragonMontagesComponent()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCDragonMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	MustNotNull(DamagedMontageDataTable);

	TArray<FDragonDamagedMontageData*> damagedDatas;
	DamagedMontageDataTable->GetAllRows<FDragonDamagedMontageData>("", damagedDatas);

	for (int32 i = 0; i < (int32)EDragonDamagedType::Max; i++)
	{
		for (FDragonDamagedMontageData* damagedData : damagedDatas)
		{
			if (damagedData->Type == (EDragonDamagedType)i)
				DamagedMontageData[i] = damagedData;
		}
	}
}

void UCDragonMontagesComponent::PlayDamagedMontage()
{
	const FDragonDamagedMontageData* data = DamagedMontageData[(int32)CurDamagedType];

	if (!!data && !!data->AnimMontage)
	{
		if(CurDamagedType == EDragonDamagedType::Dead_Left || CurDamagedType == EDragonDamagedType::Dead_Right)
			data->AnimMontage->SequenceLength = MAX_FLT;
		OwnerCharacter->PlayAnimMontage(data->AnimMontage, data->PlayerRatio, data->StartSection);
	}
}

void UCDragonMontagesComponent::PlayDamaged(EDragonDamagedType InDamagedID)
{
	CurDamagedType = InDamagedID;
	PlayDamagedMontage();
}

void UCDragonMontagesComponent::PlayDead(bool IsLeft)
{
	CurDamagedType = (IsLeft) ? EDragonDamagedType::Dead_Right : EDragonDamagedType::Dead_Left;
	PlayDamagedMontage();
}

void UCDragonMontagesComponent::StopCurMontage()
{
	OwnerCharacter->StopAnimMontage();
}
