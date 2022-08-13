#pragma once

#include "CoreMinimal.h"
#include "Modes/CAction.h"
#include "CAction_Melee.generated.h"

UENUM(BlueprintType)
enum class EDoActionType_Melee : uint8
{
	DefaultAttack,
	SpecialAttack,
	Max
};


UCLASS()
class DRAGONNEST_API ACAction_Melee : public ACAction
{
	GENERATED_BODY()

public:
	ACAction_Melee();
		
private:
	bool bPlayNextCombo;
	bool bIsComboSection;
	int32 ComboIdxCur;

private:
	void PlayCurAction();
	void OnMeleeAttack(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter, int SkillIndex, int ComboIndex);

public:
	FORCEINLINE void EnableCombo() { bIsComboSection = true; }
	FORCEINLINE void DisableCombo() { bIsComboSection = false; }

	virtual void DoAction(ESkillName Skill) override;
	virtual void BeginAnimation_Action() override;
	virtual void EndAnimation_Action() override;

	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentCollision() override;
	virtual void OffAttachmentCollision() override;

};
