#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Modes/CAction.h"
#include "CModeComponent.generated.h"



UENUM(BlueprintType)
enum class EModeType : uint8 // Á÷¾÷
{
	Unarmed,
	TwoHand,
	Max
};



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FModeChangedDelegate, EModeType, InPrevMode, EModeType, InNewMode);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONNEST_API UCModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCModeComponent();

protected:
	virtual void BeginPlay() override;

private:
	EModeType CurMode;

	UPROPERTY(EditDefaultsOnly, Category = "Modes")
		class UCModeData* ModeDatas[(int32)EModeType::Max];

public:
	UPROPERTY(BlueprintAssignable)
		FModeChangedDelegate OnModeChanged;

private:
	void ChangeMode(EModeType InMode);
	void InitDatas();

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmed() { return CurMode == EModeType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHand() { return CurMode == EModeType::TwoHand; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE UCModeData* GetCurrent() { return ModeDatas[(int32)CurMode]; }

	void SetUnarmed();
	void SetTwoHand();

	void ChangeModeToUnarmed();
	void ChangeModeToTwoHand();

	void DoAction(ESkillName Skill);
	void QuitAction();
};
