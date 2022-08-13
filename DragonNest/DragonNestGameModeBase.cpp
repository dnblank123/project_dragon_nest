#include "DragonNestGameModeBase.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"
#include "Characters/CPlayer.h"
#include "Widgets/CUserWidget_MainGame.h"
#include "Widgets/CUserWidget_ResultScreen.h"

ADragonNestGameModeBase::ADragonNestGameModeBase()
{
	CHelpers::GetClassInConstructor<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
	CHelpers::GetClassInConstructor<APlayerController>(&PlayerControllerClass, "Blueprint'/Game/Player/BP_CPlayerController.BP_CPlayerController_C'");
	CHelpers::GetClassInConstructor<UUserWidget>(&LobbyWidgetClass, "WidgetBlueprint'/Game/Widgets/BP_Widget_Lobby.BP_Widget_Lobby_C'");
	CHelpers::GetClassInConstructor<UUserWidget>(&MainGameWidgetClass, "WidgetBlueprint'/Game/Widgets/BP_Widget_MainGame.BP_Widget_MainGame_C'");
	CHelpers::GetClassInConstructor<UUserWidget>(&PausedScreenClass, "WidgetBlueprint'/Game/Widgets/BP_Widget_PausedScreen.BP_Widget_PausedScreen_C'");
	CHelpers::GetClassInConstructor<UUserWidget>(&ResultWidgetClass, "WidgetBlueprint'/Game/Widgets/BP_Widget_ResultScreen.BP_Widget_ResultScreen_C'");

	bIsMainGameStarted = false;
}

void ADragonNestGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeWidget(LobbyWidgetClass);
}

void ADragonNestGameModeBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurWidget != nullptr)
	{
		CurWidget->RemoveFromViewport();
		CurWidget = nullptr;
	}
	
	if (NewWidgetClass != nullptr)
	{
		CurWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurWidget != nullptr)
		{
			CurWidget->AddToViewport();

			if (!bIsMainGameStarted && Cast<UCUserWidget_MainGame>(CurWidget)) StartMainGame();
		}		
	}
}

void ADragonNestGameModeBase::ShowPausedScreen()
{
	MustBeTrue(Cast<UCUserWidget_MainGame>(CurWidget) != NULL);

	UGameplayStatics::SetGamePaused(GetWorld(), true);

	ChangeWidget(PausedScreenClass);

	if (PausedScreenDelegate.IsBound()) PausedScreenDelegate.Broadcast();
}

void ADragonNestGameModeBase::ShowResultScreen(bool IsWin)
{
	ChangeWidget(ResultWidgetClass);

	Cast<UCUserWidget_ResultScreen>(CurWidget)->SetText(IsWin);

	if (ResultScreenDelegate.IsBound()) ResultScreenDelegate.Broadcast();
}

void ADragonNestGameModeBase::SetWinResultScreenTimer()
{
	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			ShowResultScreen(true);
		}), ResultScreenTimer, false);
}

void ADragonNestGameModeBase::SetLoseResultScreenTimer()
{
	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			ShowResultScreen(false);
		}), ResultScreenTimer, false);
}

void ADragonNestGameModeBase::ResumeMainGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	ChangeWidget(MainGameWidgetClass);

	if (ResumeGameDelegate.IsBound()) ResumeGameDelegate.Broadcast();
}


void ADragonNestGameModeBase::StartMainGame()
{
	UCUserWidget_MainGame* widget = Cast<UCUserWidget_MainGame>(CurWidget);
	widget->EnableEnemyInfo(false);

	if (MainGameStartDelegate.IsBound()) MainGameStartDelegate.Broadcast();

	bIsMainGameStarted = true;
}

