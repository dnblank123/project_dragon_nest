#include "Characters/CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CModeComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_MainGame.h"
#include "Modes/CDamageValue.h"
#include "DragonNestGameModeBase.h"
#include "Modes/CAction.h"

ACPlayer::ACPlayer()
{
	SetComponents();
	SetMesh();
	SetAnimInstance();
	SetCamera();
	SetMovement();
	SetController();
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::OnLookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ACPlayer::OnLookRight);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACPlayer::OnStartJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACPlayer::OnStopJump);

	PlayerInputComponent->BindAction("Equip", EInputEvent::IE_Pressed, this, &ACPlayer::OnEquip);

	PlayerInputComponent->BindAction("AttackNormal", EInputEvent::IE_Pressed, this, &ACPlayer::OnNormalAttack);
	PlayerInputComponent->BindAction("Q", EInputEvent::IE_Pressed, this, &ACPlayer::OnQAttack);
	PlayerInputComponent->BindAction("E", EInputEvent::IE_Pressed, this, &ACPlayer::OnEAttack);

	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &ACPlayer::OnStartRoll);
	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Released, this, &ACPlayer::OnStopRoll);

	PlayerInputComponent->BindAction("PauseGame", EInputEvent::IE_Pressed, this, &ACPlayer::OnGamePaused);
}

void ACPlayer::SetComponents()
{
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateActorComponent<UCOptionComponent>(this, &Option, "Option");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCModeComponent>(this, &Mode, "Mode");
	CHelpers::CreateActorComponent<UCMontagesComponent>(this, &Montages, "Montages");
	CHelpers::CreateActorComponent<UAudioComponent>(this, &DashAudio, "DashAudio");

	CHelpers::GetClassInConstructor<ACDamageValue>(&DamageTextActorClass, "Blueprint'/Game/Widgets/BP_CDamageValue.BP_CDamageValue_C'");

	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
}


void ACPlayer::SetMesh()
{
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -85.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	
	USkeletalMesh* mesh;
	CHelpers::GetAssetInConstructor<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/MedievalGirl/Mesh/SK_MedievalGirl.SK_MedievalGirl'");
	GetMesh()->SetSkeletalMesh(mesh);
}

void ACPlayer::SetAnimInstance()
{
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClassInConstructor<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);
}

void ACPlayer::SetCamera()
{
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 140.0f));
	SpringArm->SetRelativeRotation(FRotator(-10.0f, 90.0f, 0.0f));
	SpringArm->TargetArmLength = 130.0f;
	SpringArm->bDoCollisionTest = true; // 카메라가 벽에 닿으면, 충돌 계산을 통해 '카메라와 캐릭터의 거리를 좁혀' 카메라가 벽을 뚫지 않게 만들어주는 프로퍼티
	SpringArm->bEnableCameraLag = false; // 카메라 지연 효과

	Camera->SetRelativeLocation(FVector(0.0f, 30.0f, 0.0f));
}

void ACPlayer::SetMovement()
{
	SpringArm->bUsePawnControlRotation = true; // 캐릭터가 회전하면 카메라도 회전할 것인가
	bUseControllerRotationYaw = true; // 카메라가 회전하면 캐릭터도 회전할 것인가
	GetCharacterMovement()->bOrientRotationToMovement = false; // 캐릭터가 이동하면 이동 방향으로 캐릭터를 회전시킬 것인가
	GetCharacterMovement()->bUseControllerDesiredRotation = true; // 캐릭터를 컨트롤러 방향으로 스무스하게 회전해 준다. 

	ChangeSpeed(true);

	GetCharacterMovement()->JumpZVelocity = Option->GetJumpPower(); // 점프 높이
	GetCharacterMovement()->AirControl = Option->GetAirControl(); // 점프하고 떨어질 때 움직임 속도

	bIsForwardKeyBeingPressed = false;
	bIsBackwardKeyBeingPressed = false;
	bIsRightKeyBeingPressed = false;
	bIsLeftKeyBeingPressed = false;

	bIsJumping = false;
	bIsJumpEnding = false;

	bIsWalkKeyBeingPressed = false;
	bIsRollKeyBeingPresesd = false;
	bIsRollKeyBeingPressedDuringRoll = false;
	bIsForwardKeyBeingPressedDuringRoll = false;
	bEndRollScheduled = false;
}

void ACPlayer::SetController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	bIsMouseCursorShowing = false;

	OnSwitchMouseCursor();

	DashAudio->Stop();

	GameMode = Cast<ADragonNestGameModeBase>(GetWorld()->GetAuthGameMode());
	MustNotNull(GameMode);

	GameMode->MainGameStartDelegate.AddDynamic(this, &ACPlayer::SetStartGame);
	GameMode->PausedScreenDelegate.AddDynamic(this, &ACPlayer::SetPausedGame);
	GameMode->ResultScreenDelegate.AddDynamic(this, &ACPlayer::SetEndGame);
	GameMode->ResumeGameDelegate.AddDynamic(this, &ACPlayer::SetResumeGame);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckMoveKey();
	CheckBackwardKey();
	CheckJumpFinished();

	CheckBeginRoll();
	CheckEndDash();

	Move();
}

void ACPlayer::SetStartGame()
{
	PlayerController->SetViewTargetWithBlend(this);

	InitWidget();

	OnSwitchMouseCursor();
}

void ACPlayer::SetPausedGame()
{
	OnSwitchMouseCursor();
}

void ACPlayer::SetResumeGame()
{
	OnSwitchMouseCursor();
	InitWidget();
}

void ACPlayer::SetEndGame()
{
	OnSwitchMouseCursor();
}

void ACPlayer::InitWidget()
{
	MainGameWidget = Cast<UCUserWidget_MainGame>(GameMode->GetCurWidget());	
	MustNotNull(MainGameWidget);

	UpdateWidget();
}

void ACPlayer::UpdateWidget()
{
	MainGameWidget->UpdatePlayerHealthBar(Status->GetHealth(), Status->GetMaxHealth());
}

void ACPlayer::Move()
{
	MustBeFalse(CurMoveDir.IsZero());

	CurMoveDir.Normalize();
	AddMovementInput(CurMoveDir);
	CurMoveDir.Set(0.0f, 0.0f, 0.0f);
}

void ACPlayer::CheckMoveKey()
{
	bIsForwardKeyBeingPressed = PlayerController->IsInputKeyDown(EKeys::W);
	bIsBackwardKeyBeingPressed = PlayerController->IsInputKeyDown(EKeys::S);
	bIsRightKeyBeingPressed = PlayerController->IsInputKeyDown(EKeys::D);
	bIsLeftKeyBeingPressed = PlayerController->IsInputKeyDown(EKeys::A);

	bIsWalkKeyBeingPressed = bIsForwardKeyBeingPressed || bIsBackwardKeyBeingPressed || bIsRightKeyBeingPressed || bIsLeftKeyBeingPressed;

	if (bIsForwardKeyBeingPressedDuringRoll) bIsForwardKeyBeingPressedDuringRoll = bIsForwardKeyBeingPressed;
}

void ACPlayer::CheckBackwardKey()
{
	if (bIsNormalWalk && bIsBackwardKeyBeingPressed)
	{
		ChangeSpeed(false);
		bIsNormalWalk = false;
	}
	else if (!bIsNormalWalk && !bIsBackwardKeyBeingPressed)
	{
		ChangeSpeed(true);
		bIsNormalWalk = true;
	}
}

void ACPlayer::ChangeSpeed(bool IsFast)
{
	if (IsFast)
	{
		GetCharacterMovement()->MaxWalkSpeed = Option->GetNormalMoveSpeed();
		GetCharacterMovement()->MinAnalogWalkSpeed = Option->GetNormalMoveSpeed();
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = Option->GetSlowMoveSpeed();
		GetCharacterMovement()->MinAnalogWalkSpeed = Option->GetSlowMoveSpeed();
	}
}

void ACPlayer::CheckJumpFinished()
{
	if (bIsJumping && GetCharacterMovement()->IsMovingOnGround()) bIsJumping = false;
}


void ACPlayer::OnMoveForward(float InAxis)
{
	MustBeFalse(bIsMouseCursorShowing);

	if ((State->IsIdle() || State->IsDashing()) && !bIsJumpEnding && Status->CanMove())
	{
		if ((State->IsDashing() && InAxis < 0)) InAxis = 1.0f;

		FVector dir = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
		dir.Z = 0.0f;
		dir.Normalize();
		CurMoveDir += dir * InAxis;
	}
}

void ACPlayer::OnMoveRight(float InAxis)
{
	MustBeFalse(bIsMouseCursorShowing);

	if (State->IsIdle() && !bIsJumpEnding && Status->CanMove())
	{
		FVector dir = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
		dir.Z = 0.0f;
		dir.Normalize();
		CurMoveDir += dir * InAxis;
	}
}

void ACPlayer::OnLookUp(float InAxis)
{
	MustBeFalse(bIsMouseCursorShowing);

	if ((State->IsIdle() || State->IsDashing()) && Status->CanMove())
		AddControllerPitchInput(InAxis * Option->GetMouseRate() * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnLookRight(float InAxis)
{
	MustBeFalse(bIsMouseCursorShowing);

	if ((State->IsIdle() || State->IsDashing()) && Status->CanMove())
		AddControllerYawInput(InAxis * Option->GetMouseRate() * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnStartJump()
{
	MustBeFalse(bIsMouseCursorShowing);

	MustBeTrue(State->IsIdle());

	bPressedJump = true;
	
	if (bIsJumping == false)
	{
		GetCharacterMovement()->Velocity.Set(0.0f, 0.0f, 0.0f);
		bIsJumping = true;
	}
}

void ACPlayer::OnStopJump()
{
	bPressedJump = false;
}

void ACPlayer::OnStartRoll()
{
	MustBeFalse(bIsMouseCursorShowing);

	bIsRollKeyBeingPresesd = true;
}

void ACPlayer::OnStopRoll()
{
	bIsRollKeyBeingPresesd = false;
	
	if (bIsRollKeyBeingPressedDuringRoll) bIsRollKeyBeingPressedDuringRoll = false;
}

void ACPlayer::CheckBeginRoll()
{
	MustBeTrue(Mode->IsTwoHand());
	
	if (bIsWalkKeyBeingPressed && bIsRollKeyBeingPresesd)
	{
		if (State->IsAttacking())
		{
			Mode->QuitAction();
			State->SetIdleState();
		}

		MustBeTrue(State->IsIdle());

		if (bIsForwardKeyBeingPressed) bIsForwardKeyBeingPressedDuringRoll = true;

		bIsRollKeyBeingPressedDuringRoll = true;

		GetCharacterMovement()->MaxWalkSpeed = Option->GetDashMoveSpeed();
		GetCharacterMovement()->MinAnalogWalkSpeed = Option->GetDashMoveSpeed();

		EStateType type = EStateType::Roll_F;

		if (bIsBackwardKeyBeingPressed)   type = EStateType::Roll_B;
		else if (bIsRightKeyBeingPressed) type = EStateType::Roll_R;
		else if (bIsLeftKeyBeingPressed)  type = EStateType::Roll_L;

		State->SetRollState(type);
		Status->SetInvincible();
		Montages->PlayRoll(type);
	}
}

void ACPlayer::CheckEndRollAndBeginDash()
{
	MustBeTrue(State->IsRolling());

	Status->SetCanBeAttacked();

	if (!bIsForwardKeyBeingPressedDuringRoll)
	{
		State->SetIdleState();

		bIsForwardKeyBeingPressedDuringRoll = false;
		bIsRollKeyBeingPressedDuringRoll = false;

		SetSpeedNormal();
	}
	else
	{
		Montages->StopCurMontage();
		BeginDash();
	}
}


void ACPlayer::BeginDash()
{
	MustBeFalse(Mode->IsUnarmed());	
	MustBeTrue(State->IsRolling());
	
	State->SetDashState();
	
	GetCharacterMovement()->MaxWalkSpeed = Option->GetDashMoveSpeed();
	GetCharacterMovement()->MinAnalogWalkSpeed = Option->GetDashMoveSpeed();	
}

void ACPlayer::CheckEndDash()
{
	if (State->IsDashing() && !bIsForwardKeyBeingPressed)
	{
		SetSpeedNormal();
		State->SetIdleState();
		DashAudio->Stop();
	}
}

void ACPlayer::OnEquip()
{
	MustBeFalse(bIsMouseCursorShowing);

	MustBeTrue(State->IsIdle());
	MustBeFalse(bIsJumping);

	DashAudio->Stop();
	(Mode->IsUnarmed()) ? Mode->SetTwoHand() : Mode->SetUnarmed();
}

void ACPlayer::OnSwitchMouseCursor()
{
	bIsMouseCursorShowing = !bIsMouseCursorShowing;

	PlayerController->bShowMouseCursor = bIsMouseCursorShowing;

	if (bIsMouseCursorShowing) PlayerController->SetInputMode(FInputModeUIOnly());
	else                       PlayerController->SetInputMode(FInputModeGameOnly());
}

// 공격 버튼을 누르면 공격합니다. 
void ACPlayer::OnNormalAttack()
{
	MustBeFalse(bIsMouseCursorShowing);
	DashAudio->Stop();

	Mode->DoAction(ESkillName::Normal);
}

void ACPlayer::OnQAttack()
{
	MustBeFalse(bIsMouseCursorShowing);
	DashAudio->Stop();

	Mode->DoAction(ESkillName::Q);
}

void ACPlayer::OnEAttack()
{
	MustBeFalse(bIsMouseCursorShowing);
	DashAudio->Stop();

	Mode->DoAction(ESkillName::E);
}

void ACPlayer::OnDamaged()
{
	DashAudio->Stop();
	State->SetDamagedState();
	Status->SetStop();
	Montages->PlayDamaged();
}

void ACPlayer::OnDead()
{
	MustBeFalse(State->IsDead())

	DashAudio->Stop();
	State->SetDeadState();
	Status->SetStop();
	Montages->PlayDead();

	GameMode->SetLoseResultScreenTimer();
}

void ACPlayer::SetSpeedNormal()
{
	GetCharacterMovement()->MaxWalkSpeed = Option->GetNormalMoveSpeed();
	GetCharacterMovement()->MinAnalogWalkSpeed = Option->GetNormalMoveSpeed();
}

void ACPlayer::OnGamePaused()
{
	GameMode->ShowPausedScreen();
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Status->IsInvincible()) return 0.0f;

	DamageInstigator = EventInstigator;
	DamagedValue = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Status->SubHealth(DamagedValue);
	DamagedValue = 0.0f;

	UpdateWidget();

	if (Status->GetHealth() <= 0.0f)
	{
		OnDead();
		return 0.0f;
	}
	
	OnDamaged();

	return Status->GetHealth();
}

void ACPlayer::ShowDamageText(FVector Location, float InDamageValue)
{
	ACDamageValue* damageText = GetWorld()->SpawnActor<ACDamageValue>(DamageTextActorClass, Location, GetControlRotation());
	damageText->SetDamageValueActor(InDamageValue * Option->GetDamageMultiplyValue());
}

