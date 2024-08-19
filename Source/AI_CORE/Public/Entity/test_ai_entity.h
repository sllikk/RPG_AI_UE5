// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perception/AIPerceptionComponent.h"
#include "test_ai_entity.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UStaticMeshComponent;

UCLASS()
class AI_CORE_API Atest_ai_entity : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UAIPerceptionStimuliSourceComponent* PerceptionStimuliSourceComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	
public:
	// Sets default values for this actor's properties
	explicit Atest_ai_entity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
