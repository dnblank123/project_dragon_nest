#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Engine/DataAsset.h"
#include "CModeData.generated.h"



USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* AnimMontageOnEquip;

	UPROPERTY(EditAnywhere)
		UAnimMontage* AnimMontageOnUnequip;
	
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMoveDuringAction = false;
};

USTRUCT(BlueprintType)
struct FSingleActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* AnimMontageOnAttack;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMoveDuringAction = false;

	UPROPERTY(EditAnywhere)
		bool bCanRotateDuringAction = false;

	UPROPERTY(EditAnywhere)
		float AttackPower = 5.0f;

	UPROPERTY(EditAnywhere)
		float SecondsToStopWhenHit;

	UPROPERTY(EditAnywhere)
		UParticleSystem* Particle;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* NiagaraSystem;

	UPROPERTY(EditAnywhere)
		FTransform ParticleTransform;
};


USTRUCT(BlueprintType)
struct FComboActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FSingleActionData> SingleActionDatas;
};



UCLASS()
class DRAGONNEST_API UCModeData : public UDataAsset
{
	GENERATED_BODY()

public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

private:
	class ACAttachment* AttachmentActor;
	class ACEquipment* EquipmentActor;
	class ACAction* ActionActor;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACEquipment> EquipmentClass; 

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACAction> ActionClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FComboActionData> ComboActionDatas;

public:
	FORCEINLINE ACEquipment* GetEquipmentActor() { return EquipmentActor; }
	FORCEINLINE ACAttachment* GetAttachmentActor() { return AttachmentActor; }
	FORCEINLINE class ACAction* GetActionActor() { return ActionActor; }

};
