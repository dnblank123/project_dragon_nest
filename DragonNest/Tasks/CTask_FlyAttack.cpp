#include "Tasks/CTask_FlyAttack.h"
#include "Characters/CDragon.h"
#include "Characters/CDragonAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCTask_FlyAttack::UCTask_FlyAttack()
{
}

EBTNodeResult::Type UCTask_FlyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACDragon* dragon = Cast<ACDragon>(OwnerComp.GetAIOwner()->GetCharacter());
	if (dragon == NULL) return EBTNodeResult::Failed;

	dragon->DoAttack(EDragonAttackType::Fly_Breath);
	
	return EBTNodeResult::Succeeded;
}
