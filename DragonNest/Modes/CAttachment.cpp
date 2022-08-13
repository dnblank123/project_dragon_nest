#include "Modes/CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ShapeComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	// 모든 콜리전을 가져온다
	GetComponents<UShapeComponent>(ShapeComponents);
	for (UShapeComponent* component : ShapeComponents)
	{
		// 언리얼 내장 델리게이트에 직접 만든 함수를 연결해준다. 
		component->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnAttachmentBeginOverlap);
		component->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnAttachmentEndOverlap);
	}

	Super::BeginPlay();

	TurnOffAllCollision();
}

void ACAttachment::OnAttachmentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MustBeFalse(OwnerCharacter == OtherActor);
	MustBeFalse(OtherActor->GetClass() == OwnerCharacter->GetClass());
	
	if (OnAttachmentBeginOverlapDelegate.IsBound())
		OnAttachmentBeginOverlapDelegate.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));

}

void ACAttachment::OnAttachmentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
											UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnAttachmentEndOverlapDelegate.IsBound())
		OnAttachmentEndOverlapDelegate.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));
}

void ACAttachment::AttachActorToSocket(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void ACAttachment::AttachCollisionToSocket(UShapeComponent* InComponent, FName InSocketName)
{
	InComponent->AttachToComponent(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void ACAttachment::TurnOnAllCollision()
{
	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	if (OnAttachmentCollisionDelegate.IsBound())
		OnAttachmentCollisionDelegate.Broadcast();
}

void ACAttachment::TurnOffAllCollision()
{
	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (OffAttachmentCollisionDelegate.IsBound())
		OffAttachmentCollisionDelegate.Broadcast();
}