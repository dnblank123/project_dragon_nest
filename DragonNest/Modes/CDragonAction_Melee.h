#pragma once

#include "CoreMinimal.h"
#include "Modes/CDragonAction.h"
#include "Components/CDragonAttackComponent.h"
#include "CDragonAction_Melee.generated.h"

UCLASS()
class DRAGONNEST_API ACDragonAction_Melee : public ACDragonAction
{
	GENERATED_BODY()

private:
	void PlayCurAction();

private:
	EDragonAttackType CurAttackType;
	bool bAlreadyDamaged;

public:
	virtual void DoAction(EDragonAttackType InAttackType) override;
	virtual void BeginAnimation_Action() override;
	virtual void EndAnimation_Action() override;

	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentCollision() override;
	virtual void OffAttachmentCollision() override;
};
