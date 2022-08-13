#include "Characters/CDragon.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DragonNestGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/CDragonStateComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CDragonMontagesComponent.h"
#include "Components/CDragonAttackComponent.h"
#include "Characters/CDragonAIController.h"
#include "Modes/CDamageValue.h"
#include "Widgets/CUserWidget_MainGame.h"

ACDragon::ACDragon()
{
	PrimaryActorTick.bCanEverTick = true;

	SetComponents();
	SetController();
	SetMesh();
	SetAnimInstance();
	SetMovement();
}

void ACDragon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACDragon::SetComponents()
{
	CHelpers::CreateActorComponent<UCDragonStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCDragonMontagesComponent>(this, &Montage, "Montage");
	CHelpers::CreateActorComponent<UCDragonAttackComponent>(this, &Attack, "Attack");

	State->OnStateChanged.AddDynamic(this, &ACDragon::OnStateTypeChanged);
}

void ACDragon::SetController()
{
	CHelpers::GetClassInConstructor<AController>(&AIControllerClass, "Blueprint'/Game/Enemy/BP_CDragonAIController.BP_CDragonAIController_C'");
}

void ACDragon::SetMesh()
{
	GetMesh()->SetRelativeLocation(FVector(-30.0f, 0.0f, -175.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	USkeletalMesh* mesh;
	CHelpers::GetAssetInConstructor<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/UnkaDragon/Meshes/UnkaDragon/SK_Unka_Realistic.SK_Unka_Realistic'");
	GetMesh()->SetSkeletalMesh(mesh);

	GetMesh()->SetGenerateOverlapEvents(true);
}

void ACDragon::SetAnimInstance()
{
	TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClassInConstructor<UAnimInstance>(&animInstanceClass, "AnimBlueprint'/Game/Enemy/ABP_CDragon.ABP_CDragon_C'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);
}


void ACDragon::SetMovement()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true; 

	bIsJumping = false;
	bAlreadySetDamagedDirection = false;
	bIsMainWidgetShowed = false;
}

void ACDragon::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ADragonNestGameModeBase>(GetWorld()->GetAuthGameMode());
	MustNotNull(GameMode);

	GameMode->MainGameStartDelegate.AddDynamic(this, &ACDragon::SetStartGame);
	GameMode->PausedScreenDelegate.AddDynamic(this, &ACDragon::SetPausedGame);
	GameMode->ResultScreenDelegate.AddDynamic(this, &ACDragon::SetEndGame);
	GameMode->ResumeGameDelegate.AddDynamic(this, &ACDragon::SetResumeGame);

	DragonAIController = Cast<ACDragonAIController>(GetController());
}

void ACDragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDragon::SetStartGame()
{
	InitWidget();

	CurDamagedStack = 0.0f;
}

void ACDragon::SetPausedGame()
{

}

void ACDragon::SetResumeGame()
{
	InitWidget();

	MainGameWidget->UpdateEnemyHealthBar(Status->GetHealth(), Status->GetMaxHealth());

	if (bIsMainWidgetShowed) ShowWidget();
}

void ACDragon::SetEndGame()
{
	Cast<ACDragonAIController>(GetController())->StopAI();
}

void ACDragon::InitWidget()
{
	MainGameWidget = Cast<UCUserWidget_MainGame>(GameMode->GetCurWidget());	
	MustNotNull(MainGameWidget);
}

void ACDragon::UpdateWidget()
{
	MustNotNull(MainGameWidget);

	MainGameWidget->UpdateEnemyHealthBar(Status->GetHealth(), Status->GetMaxHealth());

	if (!bIsMainWidgetShowed) ShowWidget();
}


void ACDragon::OnAttack()
{
}

void ACDragon::OnDamaged(float InDirection)
{
	MustBeFalse(State->IsDead());
	MustNotNull(Cast<ACDragonAIController>(GetController()));
	MustNotNull(Montage);

	if (Status->GetHealth() <= 0.0f)
	{
		State->SetDeadState();

		OnDead((InDirection < 0)); 
		return;
	}

	if (CurDamagedStack >= DamagedStackToPlayMontage)
	{
		CurDamagedStack = 0.0f;
		State->SetDamagedState();

		Montage->PlayDamaged(GetDamagedTypeFromDirection(InDirection));
		Cast<ACDragonAIController>(GetController())->StopAI();
	}

}

void ACDragon::OnDead(bool IsLeft)
{
	MustBeTrue(State->IsDead());

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), hitStopSpeed);
	UKismetSystemLibrary::K2_SetTimer(this, "RestoreDilation", hitStopSeconds, false);

	Cast<ACDragonAIController>(GetController())->StopAI();

	Montage->PlayDead(IsLeft);

	GameMode->SetWinResultScreenTimer();
}

void ACDragon::RestoreDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

EDragonDamagedType ACDragon::GetDamagedTypeFromDirection(float InDirection)
{
	if (InDirection < 0)
	{
		if (InDirection > -45.0f)       return EDragonDamagedType::Front_Right;
		else if (InDirection > -100.0f) return EDragonDamagedType::Front_Right; 
		else                            return EDragonDamagedType::Back_Right;
	}
	else
	{
		if (InDirection < 45.0f)        return EDragonDamagedType::Front_Left;
		else if (InDirection < 100.0f)  return EDragonDamagedType::Front_Left;
		else                            return EDragonDamagedType::Back_Left;
	}
}


void ACDragon::OnStateTypeChanged(EDragonStateType InPrevType, EDragonStateType InNewType)
{
}

float ACDragon::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (State->IsDead() || Status->GetHealth() <= 0.0f) return 0.0f;

	DamageInstigator = EventInstigator;
	DamagedValue = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	CurDamagedStack += DamagedValue;
		
	Status->SubHealth(DamagedValue);
	UpdateWidget();
	DamagedValue = 0.0f;
	
	DamageInstigator = NULL;
		
	return Status->GetHealth();
}

void ACDragon::SetIdleAfterDamaged()
{
	MustBeFalse(State->IsDead());
	State->SetIdleState();

	MustNotNull(Cast<ACDragonAIController>(GetController()));
	Cast<ACDragonAIController>(GetController())->RunAI();
}

void ACDragon::ShowWidget()
{
	MainGameWidget->EnableEnemyInfo(true);
	bIsMainWidgetShowed = true;
}

void ACDragon::DoAttack(EDragonAttackType InAttackID)
{
	MustBeFalse(State->IsDead());
	State->SetAttackState();
	Attack->DoAction(InAttackID);
}

