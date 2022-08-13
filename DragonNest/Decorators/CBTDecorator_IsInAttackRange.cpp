#include "Decorators/CBTDecorator_IsInAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CDragonAIController.h"
#include "Characters/CPlayer.h"


UCBTDecorator_IsInAttackRange::UCBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("IsInAttackRange");
	RadiusToAttack = 600.0f;
}

bool UCBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* ownerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ownerPawn) return false;

	ACPlayer* player = Cast<ACPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACDragonAIController::Name_Player));
	if (nullptr == player) return false;

	return (player->GetDistanceTo(ownerPawn) <= RadiusToAttack);
}
