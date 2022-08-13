#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTask_FindRandomLocation.generated.h"


UCLASS()
class DRAGONNEST_API UCTask_FindRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCTask_FindRandomLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	float RadiusToFindRandomLocation;
};
