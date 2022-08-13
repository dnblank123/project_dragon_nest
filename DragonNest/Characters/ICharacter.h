#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

class DRAGONNEST_API IICharacter
{
	GENERATED_BODY()

protected:
	class ADragonNestGameModeBase* GameMode;
	class UCUserWidget_MainGame* MainGameWidget;

protected:
	UFUNCTION()
		virtual void SetStartGame() = 0;

	UFUNCTION()
		virtual void SetPausedGame() = 0;

	UFUNCTION()
		virtual void SetResumeGame() = 0;

	UFUNCTION()
		virtual void SetEndGame() = 0;

	virtual void InitWidget() = 0;
	virtual void UpdateWidget() = 0;

};
