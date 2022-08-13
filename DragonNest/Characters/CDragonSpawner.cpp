#include "Characters/CDragonSpawner.h"
#include "Global.h"
#include "CDragon.h"
#include "Characters/CDragonAIController.h"

ACDragonSpawner::ACDragonSpawner()
{
	CHelpers::GetClassInConstructor<ACDragon>(&DragonClass, "Blueprint'/Game/Enemy/BP_CDragon.BP_CDragon_C'");
	CHelpers::GetClassInConstructor<ACDragonAIController>(&AIControllerClass, "Blueprint'/Game/Enemy/BP_CDragonAIController.BP_CDragonAIController_C'");
}

void ACDragonSpawner::BeginPlay()
{
	FTimerHandle WaitHandle;
	float WaitTime = 1.0f;

	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			ACDragon* dragon = GetWorld()->SpawnActor<ACDragon>(DragonClass, GetTransform());
			dragon->SpawnDefaultController();
			dragon->AIControllerClass = AIControllerClass;
			
		}), WaitTime, false
	); 
}