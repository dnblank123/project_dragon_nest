#pragma once

#include "CoreMinimal.h"
#include "CMontagesComponent.h"
#include "Components/ActorComponent.h"
#include "CDragonMontagesComponent.generated.h"


UENUM(BlueprintType)
enum class EDragonDamagedType : uint8
{
	Front_Left,
	Front_Right,
	Back_Left,
	Back_Right,
	Left,
	Right,
	Dead_Left,
	Dead_Right,
	Max
};


USTRUCT(BlueprintType)
struct FDragonDamagedMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EDragonDamagedType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayerRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONNEST_API UCDragonMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCDragonMontagesComponent();

protected:
	virtual void BeginPlay() override;

private:
	ACharacter* OwnerCharacter;
	
	EDragonDamagedType CurDamagedType;
	FDragonDamagedMontageData* DamagedMontageData[(int32)EDragonDamagedType::Max];

	UPROPERTY(EditDefaultsOnly, Category = "DragonDataTable")
		UDataTable* DamagedMontageDataTable;

private:
	void PlayDamagedMontage();

public:
	void PlayDamaged(EDragonDamagedType InDamagedID);
	void PlayDead(bool IsLeft);
	void StopCurMontage();
};
