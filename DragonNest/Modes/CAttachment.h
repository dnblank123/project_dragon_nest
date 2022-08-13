#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap,
												class ACharacter*, InAttacker,
												class AActor*, InAttackCauser,
												class ACharacter*, InOtherCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentEndOverlap,
												class ACharacter*, InAttacker,
												class AActor*, InAttackCauser,
												class ACharacter*, InOtherCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentCollision);




UCLASS()
class DRAGONNEST_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

protected:
	TArray<class UShapeComponent*> ShapeComponents;

	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Scene;

public:
	UPROPERTY(BlueprintAssignable)
		FAttachmentBeginOverlap OnAttachmentBeginOverlapDelegate;

	UPROPERTY(BlueprintAssignable)
		FAttachmentEndOverlap OnAttachmentEndOverlapDelegate;

	UPROPERTY(BlueprintAssignable)
		FAttachmentCollision OnAttachmentCollisionDelegate;

	UPROPERTY(BlueprintAssignable)
		FAttachmentCollision OffAttachmentCollisionDelegate;

protected:
	UFUNCTION()
		void OnAttachmentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
										AActor* OtherActor,
										UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex,
										bool bFromSweep, 
										const FHitResult& SweepResult);

	UFUNCTION()
		void OnAttachmentEndOverlap(UPrimitiveComponent* OverlappedComponent,
									AActor* OtherActor,
									UPrimitiveComponent* OtherComp,
									int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void AttachActorToSocket(FName InSocketName);

	UFUNCTION(BlueprintCallable)
		void AttachCollisionToSocket(UShapeComponent* InComponent, FName InSocketName);

public:
	UFUNCTION(BlueprintCallable)
		void TurnOnAllCollision();

	UFUNCTION(BlueprintCallable)
		void TurnOffAllCollision();

	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequipFinished();


};
