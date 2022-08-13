#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDamageValue.generated.h"

UCLASS()
class DRAGONNEST_API ACDamageValue : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDamageValue();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USceneComponent* Scene;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UWidgetComponent* Widget;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetDamageValueActor(float InDamageValue);
};
