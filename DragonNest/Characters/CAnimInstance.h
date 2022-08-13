#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CModeComponent.h"
#include "Components/CStateComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class DRAGONNEST_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	ACharacter* OwnerCharacter;
	class ACPlayer* Player;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EStateType CurStateType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EModeType CurModeType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bIsWalking;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bIsJumping;
	
	
private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
		void OnModeChanged(EModeType InPrevMode, EModeType InNewMode);
	
};
