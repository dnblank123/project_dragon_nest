#pragma once

#include "CoreMinimal.h"
#include "ICharacter.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class DRAGONNEST_API ACPlayer : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	APlayerController* PlayerController;
	TSubclassOf<class ACDamageValue> DamageTextActorClass;

	FVector CurMoveDir;
	bool bIsNormalWalk;
	bool bIsMouseCursorShowing;

	class AController* DamageInstigator;
	float DamagedValue;
	float DamagedDirection;

	UPROPERTY(VisibleDefaultsOnly)  
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCModeComponent* Mode;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UAudioComponent* DashAudio;

public:
	bool bIsJumping;
	bool bIsJumpEnding;

	bool bIsForwardKeyBeingPressed;
	bool bIsBackwardKeyBeingPressed;
	bool bIsRightKeyBeingPressed;
	bool bIsLeftKeyBeingPressed;

	bool bIsWalkKeyBeingPressed;
	bool bIsRollKeyBeingPresesd;
	bool bIsForwardKeyBeingPressedDuringRoll;
	bool bIsRollKeyBeingPressedDuringRoll;

	bool bEndRollScheduled;


private:
	void SetComponents();
	void SetMesh();
	void SetAnimInstance();
	void SetCamera();
	void SetMovement();
	void SetController();

	void Move();
	void CheckMoveKey();
	void CheckBackwardKey();
	void ChangeSpeed(bool IsFast);
	void CheckJumpFinished();

	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);

	void OnLookUp(float InAxis);
	void OnLookRight(float InAxis);

	void OnStartJump();
	void OnStopJump();

	void OnStartRoll();
	void OnStopRoll();

	void CheckBeginRoll();
	void BeginDash();
	void CheckEndDash();
			
	void OnEquip();
	void OnSwitchMouseCursor();
	void OnNormalAttack();
	void OnQAttack();
	void OnEAttack();
	void OnDamaged();
	void OnDead();

	void SetSpeedNormal();
	void OnGamePaused();

protected:
	UFUNCTION()
		virtual void SetStartGame() override;

	UFUNCTION()
		virtual void SetPausedGame() override;

	UFUNCTION()
		virtual void SetResumeGame() override;

	UFUNCTION()
		virtual void SetEndGame() override;

	virtual void InitWidget() override;
	virtual void UpdateWidget() override;

public:
	FORCEINLINE EStateType GetCurState() { return State->GetCurState(); }
	FORCEINLINE UCOptionComponent* GetOption() { return Option; }
	FORCEINLINE void SetIsJumpEnding(bool InIsJumpEnding) { bIsJumpEnding = InIsJumpEnding; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void CheckEndRollAndBeginDash();
	void ShowDamageText(FVector Location, float InDamageValue);
};
