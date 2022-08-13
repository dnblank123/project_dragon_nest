#include "Characters/CDragonAIController.h"
#include "Global.h"
#include "Characters/CDragon.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


const FName ACDragonAIController::Name_HomePos(TEXT("HomePos"));
const FName ACDragonAIController::Name_PatrolPos(TEXT("PatrolPos"));
const FName ACDragonAIController::Name_Player(TEXT("Player"));
const FName ACDragonAIController::Name_AttackID(TEXT("AttackID"));
const FName ACDragonAIController::Name_CanAttack(TEXT("CanAttack"));


ACDragonAIController::ACDragonAIController()
{
	CHelpers::GetAssetInConstructor<UBehaviorTree>(&BTAsset, "BehaviorTree'/Game/Enemy/DragonBT/BT_Dragon.BT_Dragon'");
	CHelpers::GetAssetInConstructor<UBlackboardData>(&BBAsset, "BlackboardData'/Game/Enemy/DragonBT/BB_Dragon.BB_Dragon'");	
}

void ACDragonAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACDragonAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerDragon = Cast<ACDragon>(InPawn);

	RunAI();
}

void ACDragonAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard)) RunBehaviorTree(BTAsset);
}

void ACDragonAIController::StopAI()
{
	UBehaviorTreeComponent* btComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	MustNotNull(btComponent);

	btComponent->StopTree(EBTStopMode::Safe);
}
