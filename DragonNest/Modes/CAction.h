#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Modes/CModeData.h"
#include "CAction.generated.h"


UENUM()
enum class ESkillName : uint8
{
	Normal,
	Q,
	E,
	Max
};



UCLASS()
class DRAGONNEST_API ACAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAction();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCModeComponent* Mode;

	class UNiagaraComponent* Niagara;

	TArray<FComboActionData> ComboActionDatas; // Mode(TwoHand)에 대한 모든 콤보 데이터를 가지고 있다. 
	TArray<ACharacter*> DamagedCharacters;

	int32 SkillIdxCur;

protected:
	void SetAndShowNiagaraEffect(FVector Location, FRotator Rotation, int SkillIndex, int ComboIndex);

public:
	FORCEINLINE void SetComboDatas(TArray<FComboActionData> InDatas) { ComboActionDatas = InDatas; }

	virtual void DoAction(ESkillName Skill) {}
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
	
	void ResetDamagedCharacters();

};
