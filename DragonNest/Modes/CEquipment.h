#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Modes/CModeData.h"
#include "CEquipment.generated.h"

UENUM()
enum class EEquipState : uint8
{
	None,
	Equip,
	Unequip
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnequipDelegate);


UCLASS()
class DRAGONNEST_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipment();

protected:
	virtual void BeginPlay() override;

private:
	EEquipState EquipStateForAnimation;
	FEquipmentData EquipmentData;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
	
public:
	UPROPERTY(BlueprintAssignable)
		FEquipDelegate OnEquip;

	UPROPERTY(BlueprintAssignable)
		FUnequipDelegate OnUnequipFinished;

public:
	void Equip();
	void Unequip();
	
	void BeginAnimation_Equip();
	void EndAnimation_Equip();
	
	FORCEINLINE void SetEquipmentData(FEquipmentData InData) { EquipmentData = InData; }
	FORCEINLINE bool IsEquipState() { return EquipStateForAnimation == EEquipState::Equip; }
	FORCEINLINE bool IsUnequipState() { return EquipStateForAnimation == EEquipState::Unequip; }
	
};
