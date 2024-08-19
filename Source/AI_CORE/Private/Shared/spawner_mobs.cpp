// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/spawner_mobs.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
Aspawner_mobs::Aspawner_mobs(): Spawners(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void Aspawner_mobs::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnerMobsClass != nullptr && BoxComponent != nullptr)
	{
		const FVector& BoxOrigin = BoxComponent->GetComponentLocation();
		const FVector& BoxExtent = BoxComponent->GetScaledBoxExtent();
		

		for (uint8 i = 0; i < Spawners; ++i)
		{
			const FVector& SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);	
			const FRotator& SpawnRotator = FRotator::ZeroRotator; 

			FActorSpawnParameters ActorSpawnParameters;
			const APawn* SpawnedMob = GetWorld()->SpawnActor<APawn>(SpawnerMobsClass, SpawnLocation, SpawnRotator, ActorSpawnParameters);
		}		
	}	
}





