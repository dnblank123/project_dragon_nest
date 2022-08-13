#include "Services/CBTService_CheckAttackFinished.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CDragonAIController.h"
#include "Characters/CDragon.h"

UCBTService_CheckAttackFinished::UCBTService_CheckAttackFinished()
{
	NodeName = TEXT("CheckAttackFinished");
	Interval = 0.3f;
}

void UCBTService_CheckAttackFinished::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACDragon* dragon = Cast<ACDragon>(OwnerComp.GetAIOwner()->GetCharacter());
	if (dragon == nullptr) return;

	bool bCanAttack = !dragon->IsAttacking();

	if (bCanAttack) OwnerComp.GetBlackboardComponent()->SetValueAsBool(ACDragonAIController::Name_CanAttack, bCanAttack);
	else            OwnerComp.GetBlackboardComponent()->SetValueAsBool(ACDragonAIController::Name_CanAttack, nullptr);
}
