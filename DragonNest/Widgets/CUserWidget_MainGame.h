#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_MainGame.generated.h"

UCLASS()
class DRAGONNEST_API UCUserWidget_MainGame : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetPlayerName(const FString& InName);

	UFUNCTION(BlueprintImplementableEvent)
		void SetEnemyName(const FString& InName);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdatePlayerHealthBar(float Health, float MaxHealth);
	
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateEnemyHealthBar(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent)
		void EnableEnemyInfo(bool Active);
};
