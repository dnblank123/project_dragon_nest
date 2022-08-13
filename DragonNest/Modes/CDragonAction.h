#pragma once

#include "CoreMinimal.h"
#include "CDragonAttackData.h"
#include "Components/CDragonAttackComponent.h"
#include "Components/CDragonMontagesComponent.h"
#include "GameFramework/Actor.h"
#include "CDragonAction.generated.h"

UCLASS()
class DRAGONNEST_API ACDragonAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDragonAction();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCDragonStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCDragonAttackComponent* Attack;

	TArray<FSingleAttackData> AttackDatas;
	
public:
	FORCEINLINE void SetActionDatas(TArray<FSingleAttackData> InDatas) { AttackDatas = InDatas; }

public:
	virtual void DoAction(EDragonAttackType InAttackType) {}
	virtual void BeginAnimation_Action() {}
	virtual void EndAnimation_Action() {}


	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnAttachmentCollision() {}

	UFUNCTION()
		virtual void OffAttachmentCollision() {}



};
