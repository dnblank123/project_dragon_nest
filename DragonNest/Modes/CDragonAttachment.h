#pragma once

#include "CoreMinimal.h"
#include "Modes/CAttachment.h"
#include "CDragonAttachment.generated.h"


UENUM(BlueprintType)
enum class EDragonAttachmentType : uint8
{
	Hand_Right,
	Hand_Left,
	Tail_Socket,
	Head_Socket,
	Max
};


UCLASS()
class DRAGONNEST_API ACDragonAttachment : public ACAttachment
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void TurnOnDragonCollision(EDragonAttachmentType InType);
};
