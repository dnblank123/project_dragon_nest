#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_DamageText.generated.h"

UCLASS()
class DRAGONNEST_API UCUserWidget_DamageText : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetDamageText(float DamageValue);
};
