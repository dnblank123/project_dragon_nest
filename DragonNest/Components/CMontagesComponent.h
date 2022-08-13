#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CMontagesComponent.generated.h"


USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayerRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONNEST_API UCMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMontagesComponent();

protected:
	virtual void BeginPlay() override;

private:	
	ACharacter* OwnerCharacter;
	EStateType State;
	FMontageData* MontageData[(int32)EStateType::Max];

	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* MontageDataTable;

private:
	void PlayMontage();

public:
	void PlayEquip();
	void PlayRoll(EStateType type);
	void PlayDamaged();
	void PlayDead();

	void StopCurMontage();
};
