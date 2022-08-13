#pragma once

#include "CoreMinimal.h"
#include "Modes/CDragonAttackData.h"
#include "Components/ActorComponent.h"
#include "CDragonAttackComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONNEST_API UCDragonAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCDragonAttackComponent();

protected:
	virtual void BeginPlay() override;

private:
	EDragonAttackType CurAttackType;

	UPROPERTY(EditDefaultsOnly, Category = "AttackDatas")
		class UCDragonAttackData* AttackData;

private:
	void InitData();

public:
	FORCEINLINE class UCDragonAttackData* GetAttackData() { return AttackData; }
	FORCEINLINE class ACDragonAttachment* GetAttachment() { return AttackData->GetAttachmentActor(); }

	void DoAction(EDragonAttackType InNewAction);
	void QuitAction();

	void ChangeAttackType(EDragonAttackType InNewAction);
	void EnableCollision();
};
