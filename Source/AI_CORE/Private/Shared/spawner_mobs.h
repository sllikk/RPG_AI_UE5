// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "spawner_mobs.generated.h"

class UBoxComponent;

UCLASS(MinimalAPI)
class Aspawner_mobs : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Spawn")
	TSubclassOf<APawn> SpawnerMobsClass; 

	UPROPERTY(EditAnywhere, Category="Spawn")
	uint8 Spawners;

	UPROPERTY(VisibleAnywhere, Category="BoxSpawnCollision")
	UBoxComponent* BoxComponent;	
	
public:	
	// Sets default values for this actor's properties
	explicit Aspawner_mobs();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	
	
};
