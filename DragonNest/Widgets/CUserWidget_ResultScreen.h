#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_ResultScreen.generated.h"

UCLASS()
class DRAGONNEST_API UCUserWidget_ResultScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetText(bool IsWin);
};
