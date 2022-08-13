#include "Modes/CDamageValue.h"
#include "Global.h"
#include "Components/WidgetComponent.h"

ACDamageValue::ACDamageValue()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UWidgetComponent>(this, &Widget, "Widget", Scene);
}

void ACDamageValue::BeginPlay()
{
	Super::BeginPlay();

}

void ACDamageValue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

