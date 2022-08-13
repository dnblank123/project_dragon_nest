#include "Tasks/CTask_FindRandomLocation.h"
#include "Global.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CDragonAIController.h"


UCTask_FindRandomLocation::UCTask_FindRandomLocation()
{
	NodeName = TEXT("FindRandomLocation");
	RadiusToFindRandomLocation = 1000.0f;
}

EBTNodeResult::Type UCTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ownerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ownerPawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* nav = UNavigationSystemV1::GetNavigationSystem(ownerPawn->GetWorld());
	if (nullptr == nav) return EBTNodeResult::Failed;
	
	FVector ownerLoc = ownerPawn->GetActorLocation();

	FNavLocation nextLoc;
	if (nav->GetRandomPointInNavigableRadius(ownerLoc, RadiusToFindRandomLocation, nextLoc))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ACDragonAIController::Name_PatrolPos, nextLoc.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
