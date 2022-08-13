#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTask_RandomFrontAttack.generated.h"


UCLASS()
class DRAGONNEST_API UCTask_RandomFrontAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCTask_RandomFrontAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
