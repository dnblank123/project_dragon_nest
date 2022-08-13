#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDragonSpawner.generated.h"

UCLASS()
class DRAGONNEST_API ACDragonSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDragonSpawner();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class ACDragon> DragonClass;
	TSubclassOf<class ACDragonAIController> AIControllerClass;
};
