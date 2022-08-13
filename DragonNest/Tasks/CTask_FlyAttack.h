#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTask_FlyAttack.generated.h"

UCLASS()
class DRAGONNEST_API UCTask_FlyAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCTask_FlyAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
