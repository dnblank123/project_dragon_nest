#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DragonNestGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMainGame);


UCLASS()
class DRAGONNEST_API ADragonNestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADragonNestGameModeBase();

protected:
	virtual void BeginPlay() override;

private:
	bool bIsMainGameStarted;
	float ResultScreenTimer = 3.0f;

public:
	UUserWidget* CurWidget;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> MainGameWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> ResultWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UUserWidget> PausedScreenClass;

	UPROPERTY(BlueprintAssignable)
		FMainGame MainGameStartDelegate;
	
	UPROPERTY(BlueprintAssignable)
		FMainGame PausedScreenDelegate;

	UPROPERTY(BlueprintAssignable)
		FMainGame ResumeGameDelegate;

	UPROPERTY(BlueprintAssignable)
		FMainGame ResultScreenDelegate;

private:
	void StartMainGame();

public:
	FORCEINLINE UUserWidget* GetCurWidget() { return CurWidget; }

	UFUNCTION(BlueprintCallable)
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	
	void ShowPausedScreen();
	void ShowResultScreen(bool IsWin);

	void SetWinResultScreenTimer();
	void SetLoseResultScreenTimer();

	UFUNCTION(BlueprintCallable)
		void ResumeMainGame();
};
