#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CDragonAIController.generated.h"

UCLASS()
class DRAGONNEST_API ACDragonAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACDragonAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class ACDragon* OwnerDragon;

	UPROPERTY()
		UBehaviorTree* BTAsset;

	UPROPERTY()
		UBlackboardData* BBAsset;

public:
	static const FName Name_HomePos;
	static const FName Name_PatrolPos;
	static const FName Name_Player;
	static const FName Name_AttackID;
	static const FName Name_CanAttack;

public:
	void RunAI();
	void StopAI();

};
