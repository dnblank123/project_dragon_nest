#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_DetectPlayer.generated.h"


UCLASS()
class DRAGONNEST_API UCBTService_DetectPlayer : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_DetectPlayer();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float RadiusToDetect;

};
