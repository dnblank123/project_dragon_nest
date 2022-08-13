#pragma once

#include "CoreMinimal.h"
#include "ICharacter.h"
#include "Components/CDragonAttackComponent.h"
#include "Components/CDragonMontagesComponent.h"
#include "Components/CDragonStateComponent.h"
#include "GameFramework/Character.h"
#include "Widgets/CUserWidget_DamageText.h"
#include "CDragon.generated.h"


UCLASS()
class DRAGONNEST_API ACDragon : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACDragon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCDragonStateComponent* State;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCDragonMontagesComponent* Montage;

	UPROPERTY(VisibleDefaultsOnly)
		class UCDragonAttackComponent* Attack;

	class AController* DamageInstigator;
	class ACDragonAIController* DragonAIController;

	bool bIsStartGameSet;
	bool bIsMainWidgetShowed;

	float DamagedValue;
	float CurDamagedStack;
	float DamagedStackToPlayMontage = 25.0f;
	float hitStopSpeed = 3e-1f;
	float hitStopSeconds = 1.0f;

public:
	bool bIsJumping;
	bool bAlreadySetDamagedDirection;

private:
	void SetComponents();
	void SetController();
	void SetMesh();
	void SetAnimInstance();
	void SetMovement();

	void OnAttack();
	void OnDead(bool IsLeft);

	EDragonDamagedType GetDamagedTypeFromDirection(float InDirection);

	UFUNCTION()
		void RestoreDilation();

	UFUNCTION()
		void OnStateTypeChanged(EDragonStateType InPrevType, EDragonStateType InNewType);

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
	FORCEINLINE EDragonStateType GetCurState() { return State->GetCurState(); }
	FORCEINLINE bool IsAttacking() { return State->IsAttacking(); }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void OnDamaged(float InDirection);

	void SetIdleAfterDamaged();
	void ShowWidget();

	void DoAttack(EDragonAttackType InAttackID);
};
