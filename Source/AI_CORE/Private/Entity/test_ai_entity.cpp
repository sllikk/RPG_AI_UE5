// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/test_ai_entity.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Team.h"


// Sets default values
Atest_ai_entity::Atest_ai_entity(): PerceptionStimuliSourceComponent(nullptr), StaticMeshComponent(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("PerceptionStimulus"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComponent;


}

// Called when the game starts or when spawned
void Atest_ai_entity::BeginPlay()
{
	Super::BeginPlay();

	if (PerceptionStimuliSourceComponent->IsValidLowLevel())
	{
		PerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
		PerceptionStimuliSourceComponent->RegisterForSense(UAISense_Hearing::StaticClass());
		PerceptionStimuliSourceComponent->RegisterForSense(UAISense_Team::StaticClass());
		PerceptionStimuliSourceComponent->RegisterForSense(UAISense_Damage::StaticClass());
	}
	
}

// Called every frame
void Atest_ai_entity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

