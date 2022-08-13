#pragma once

#include "CoreMinimal.h"
#include "CDragonAttachment.h"
#include "Engine/DataAsset.h"
#include "CDragonAttackData.generated.h"

UENUM(BlueprintType)
enum class EDragonAttackType : uint8
{
	Front_Stump,
	Front_Claws_Left,
	Front_Claws_Right,
	Front_Tail_Left,
	Front_Tail_Right,
	FarFront_Bite,
	FarFront_FireBall,
	FarFront_Breath,
	Fly_Breath,
	Max
};


USTRUCT(BlueprintType)
struct FSingleAttackData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		TArray<EDragonAttachmentType> AttachmentsToActive;

	UPROPERTY(EditAnywhere)
		float AttackPower;

	UPROPERTY(EditAnywhere)
		bool bKeepDamaging = false;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};


UCLASS()
class DRAGONNEST_API UCDragonAttackData : public UDataAsset
{
	GENERATED_BODY()

public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

private:
	class ACDragonAttachment* AttachmentActor;
	class ACDragonAction* DoActionActor;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACDragonAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACDragonAction> DoActionClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FSingleAttackData> SingleActionDatas;
	
public:
	FORCEINLINE ACDragonAttachment* GetAttachmentActor() { return AttachmentActor; }
	FORCEINLINE class ACDragonAction* GetDoActionActor() { return DoActionActor; }
	FORCEINLINE FSingleAttackData GetAttackData(EDragonAttackType InType) { return SingleActionDatas[(int32)InType]; }
};
