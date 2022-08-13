#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CDragonStateComponent.h"
#include "CDragonAnimInstance.generated.h"


UCLASS()
class DRAGONNEST_API UCDragonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	ACharacter* OwnerCharacter;
	class ACDragon* Dragon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bIsJumping;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EDragonStateType CurStateType;

private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
