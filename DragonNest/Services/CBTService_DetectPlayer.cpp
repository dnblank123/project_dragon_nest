#include "Services/CBTService_DetectPlayer.h"
#include "Characters/CPlayer.h"
#include "Characters/CDragonAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "DrawDebugHelpers.h"


UCBTService_DetectPlayer::UCBTService_DetectPlayer()
{
	NodeName = TEXT("DetectPlayer");
	RadiusToDetect = 1000.0f;
	Interval = 0.3f;
}

void UCBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	APawn* ownerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ownerPawn) return;

	UWorld* world = ownerPawn->GetWorld();
	if (nullptr == world) return;

	FVector ownerLoc = ownerPawn->GetActorLocation();

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams collisionQueryParam(NAME_None, false, ownerPawn);
	bool bResult = world->OverlapMultiByChannel(overlapResults,
												ownerLoc,
												FQuat::Identity,
												ECollisionChannel::ECC_GameTraceChannel2,
												FCollisionShape::MakeSphere(RadiusToDetect),
												collisionQueryParam);

	if (bResult)
	{
		for (FOverlapResult overlapResult : overlapResults)
		{
			ACPlayer* player = Cast<ACPlayer>(overlapResult.GetActor());
			if (player && player->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ACDragonAIController::Name_Player, player);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(ACDragonAIController::Name_Player, nullptr);
}
