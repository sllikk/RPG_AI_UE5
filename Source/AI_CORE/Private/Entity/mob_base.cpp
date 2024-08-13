// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_CORE/Public/Entity/mob_base.h"

#include "NavigationInvokerComponent.h"
#include "Components/WidgetComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Team.h"

// Sets default values
Amob_base::Amob_base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.Get()), pPerceptionStimuliSourceComponent(nullptr), pNavigationInvokerComponent(nullptr),
	  pWidgetComponent(nullptr)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	pPerceptionStimuliSourceComponent = ObjectInitializer.CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(this, TEXT("MOBS_PERCEPTION_STIMULUS"));	
	pNavigationInvokerComponent = ObjectInitializer.CreateDefaultSubobject<UNavigationInvokerComponent>(this, TEXT("MOBS_NAVIGATION_INVOKER"));		
	pWidgetComponent = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("MOBS_WIDGET"));

}

void Amob_base::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (pPerceptionStimuliSourceComponent->IsValidLowLevel())
	{
		pPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
		pPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Damage::StaticClass());
		pPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Team::StaticClass());
	}
}

// Called when the game starts or when spawned
void Amob_base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Amob_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float Amob_base::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


