#include "Tasks/CTask_RandomFrontAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CDragon.h"
#include "Characters/CDragonAIController.h"

UCTask_RandomFrontAttack::UCTask_RandomFrontAttack()
{
}

EBTNodeResult::Type UCTask_RandomFrontAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACDragon* dragon = Cast<ACDragon>(OwnerComp.GetAIOwner()->GetCharacter());
	if (dragon == nullptr) return EBTNodeResult::Failed;

	int attackID = OwnerComp.GetBlackboardComponent()->GetValueAsEnum(ACDragonAIController::Name_AttackID);
	attackID = FMath::RandRange(0, static_cast<int>(EDragonAttackType::Max) - 2 - 2); // -2-2°íÄ¡±â

	EDragonAttackType type = static_cast<EDragonAttackType>(attackID);
	dragon->DoAttack(type);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ACDragonAIController::Name_CanAttack, false);

	return EBTNodeResult::Succeeded;
}
