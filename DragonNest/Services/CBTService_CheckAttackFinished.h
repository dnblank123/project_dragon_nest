#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_CheckAttackFinished.generated.h"

UCLASS()
class DRAGONNEST_API UCBTService_CheckAttackFinished : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_CheckAttackFinished();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
