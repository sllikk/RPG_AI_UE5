// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_CORE/Public/Entity/mob_base.h"

#include "NavigationInvokerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/CrowdManager.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
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
		pPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Hearing::StaticClass());
	}
}

// Called when the game starts or when spawned
void Amob_base::BeginPlay()
{
	Super::BeginPlay();

	UCrowdManager* CrowdManager = UCrowdManager::GetCurrent(this);
	if(CrowdManager != nullptr)
	{
		CrowdManager->RegisterAgent(this);
	}
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

//-------------------------------ICrowdAgentInterface-----------------------------------------------------------------------------------//
FVector Amob_base::GetCrowdAgentLocation() const
{
	return  GetActorLocation();
}

FVector Amob_base::GetCrowdAgentVelocity() const
{
	return GetCharacterMovement()->GetVelocityForRVOConsideration();
}

void Amob_base::GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const
{
	CylinderRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	CylinderHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}

float Amob_base::GetCrowdAgentMaxSpeed() const
{
	return GetCharacterMovement()->GetMaxSpeed();
}

int32 Amob_base::GetCrowdAgentAvoidanceGroup() const
{
	return ICrowdAgentInterface::GetCrowdAgentAvoidanceGroup();
}

int32 Amob_base::GetCrowdAgentGroupsToAvoid() const
{
	return 1;
}

int32 Amob_base::GetCrowdAgentGroupsToIgnore() const
{
	return ICrowdAgentInterface::GetCrowdAgentGroupsToIgnore();
}


