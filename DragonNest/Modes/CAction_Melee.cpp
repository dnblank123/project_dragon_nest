#include "Modes/CAction_Melee.h"
#include "Global.h"
#include "Characters/CDragon.h"
#include "Characters/CPlayer.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NiagaraComponent.h"


ACAction_Melee::ACAction_Melee()
{
	bIsComboSection = false;
	bPlayNextCombo = false;
}

void ACAction_Melee::PlayCurAction()
{
	FSingleActionData& data = ComboActionDatas[SkillIdxCur].SingleActionDatas[ComboIdxCur];
	OwnerCharacter->PlayAnimMontage(data.AnimMontageOnAttack, data.PlayRatio, data.StartSection);
}

void ACAction_Melee::DoAction(ESkillName Skill)
{
	Super::DoAction(Skill);
	
	MustBeTrue(ComboActionDatas.Num() > 0);

	ResetDamagedCharacters();

	if (bIsComboSection) // 콤보 구간에서, 클릭을 또해서 들어왔다면? bPlayNextCombo 를 활성화 한다. 
	{
		bIsComboSection = false;
		bPlayNextCombo = true;
		return;
	}

	MustBeTrue(State->IsIdle());


	// change to attack State
	State->SetAttackState();

	// pick skill
	SkillIdxCur = (int32)Skill;
	ComboIdxCur = 0;
	
	PlayCurAction();
}

void ACAction_Melee::BeginAnimation_Action()
{
	Super::BeginAnimation_Action();
	
	MustBeTrue(bPlayNextCombo);
	MustBeTrue((ComboIdxCur + 1) <= ComboActionDatas[(int32)SkillIdxCur].SingleActionDatas.Num())
		
	bPlayNextCombo = false;
	
	OwnerCharacter->StopAnimMontage();
	ComboIdxCur++;
	PlayCurAction();
}

void ACAction_Melee::EndAnimation_Action()
{
	Super::EndAnimation_Action();

	const FSingleActionData& data = ComboActionDatas[SkillIdxCur].SingleActionDatas[ComboIdxCur];
	OwnerCharacter->StopAnimMontage(data.AnimMontageOnAttack);

	State->SetIdleState();
	ComboIdxCur = 0;

	ResetDamagedCharacters();
}

void ACAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);

	OnMeleeAttack(InAttacker, InAttackCauser, InOtherCharacter, SkillIdxCur, ComboIdxCur);
}

void ACAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InAttackCauser, InOtherCharacter);
}

void ACAction_Melee::OnAttachmentCollision()
{
	Super::OnAttachmentCollision();
}

void ACAction_Melee::OffAttachmentCollision()
{
	Super::OffAttachmentCollision();
	
	ResetDamagedCharacters();
}

void ACAction_Melee::OnMeleeAttack(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter, int SkillIndex, int ComboIndex)
{
	MustNotNull(InOtherCharacter);
	MustBeTrue(State->IsAttacking());

	for (const ACharacter* other : DamagedCharacters)
		if (InOtherCharacter == other) return;

	DamagedCharacters.Add(InOtherCharacter);


	ACDragon* dragon = Cast<ACDragon>(InOtherCharacter);
	MustNotNull(dragon);
	
	// give damage
	FDamageEvent e;
	float power = ComboActionDatas[SkillIndex].SingleActionDatas[ComboIndex].AttackPower;

	float damageBoundary = power * 0.1f;
	power += FMath::FRandRange(-damageBoundary, damageBoundary);

	dragon->TakeDamage(power, e, OwnerCharacter->GetController(), this);


	// show damage & effect
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);

	TArray<AActor*> ignoreActors;
	FHitResult hitResult;

	if (player != NULL)
	{
		if (UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(),
			player->GetActorLocation(), player->GetActorForwardVector() * 10.0f, "Pawn", false, ignoreActors, EDrawDebugTrace::ForOneFrame,
			hitResult, true, FLinearColor::Green, FLinearColor::Red))
		{
			SetAndShowNiagaraEffect(hitResult.Location, player->GetActorRotation(), SkillIndex, ComboIndex);
			player->ShowDamageText(hitResult.Location + FVector(0.0f, 20.0f, 20.0f), power);
		}
	}


	// set damaged direction
	// 절대 각도 구하기
	FVector dest = FVector(OwnerCharacter->GetActorLocation().X, OwnerCharacter->GetActorLocation().Y, 0.0f);
	FVector start = FVector(dragon->GetActorLocation().X, dragon->GetActorLocation().Y, 0.0f);

	FVector attackedDir = (dest - start).GetSafeNormal();

	FVector forward = dragon->GetActorForwardVector();

	float dot = FVector::DotProduct(forward, attackedDir);
	float acos = FMath::Acos(dot);
	float degree = FMath::RadiansToDegrees(acos);


	// 방향 구하기
	FVector cross = FVector::CrossProduct(forward, attackedDir);
	if (cross.Z < 0)  degree = -degree;

	dragon->OnDamaged(degree);
}