// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <ESense.h>
#include "CoreMinimal.h"
#include "AIController.h"
#include "Entity/mob_base.h"
#include "Perception/AIPerceptionTypes.h"
#include "base_controller_mobs.generated.h"

/** Forward declaration to improve compiling times */
class UAISenseConfig_Sight;	
class UAISenseConfig_Damage;	
class UAISenseConfig_Team;	
class UAISenseConfig_Hearing;
class AActor;
class Amob_base;
class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS(Blueprintable)
class AI_CORE_API Abase_controller_mobs : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Sense", meta=(AllowPrivateAccess = "true"))	
	UAISenseConfig_Sight* pConfig_Sight;

	UPROPERTY(EditAnywhere, Category="Sense", meta=(AllowPrivateAccess = "true"))	
	UAISenseConfig_Damage* pConfig_Damage;

	UPROPERTY(EditAnywhere, Category="Sense", meta=(AllowPrivateAccess = "true"))
	UAISenseConfig_Team* pConfig_Team;

	UPROPERTY(EditAnywhere, Category="Sense", meta=(AllowPrivateAccess = "true"))
	UAISenseConfig_Hearing* pConfig_Hearing;

	UPROPERTY(EditAnywhere, Category="Behavior", meta=(AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BTC;
	
	UPROPERTY(EditAnywhere, Category="Behavior", meta=(AllowPrivateAccess = "true"))
	UBlackboardComponent* BBC;
	
public:	

	explicit Abase_controller_mobs(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;	

public:

	// Interface GenericTeamId
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	virtual FGenericTeamId GetGenericTeamId() const override;

	// Sense and Perception
	UFUNCTION()
	virtual void UpdatePerception(const TArray<AActor*>& UpdateActors);
	virtual bool CanSenseActors(AActor* SenseActor, ESenseConfig SenseConfig, FAIStimulus& Stimulus);

	FORCEINLINE void SetTeamID(const uint8& id) { TeamID = id; };
	FORCEINLINE void SetRadiusSight(double flradius ) { flradius_sight = flradius; };	
	FORCEINLINE void SetRadiusHearing(double flradius ) { flradius_hearing = flradius; };	

	// func sense
	virtual void HandleSightActors(AActor* OtherActor);
	virtual void HandleSightLostActors(AActor* OtherActor);
	virtual void HandleDamageActors(AActor* OtherActor);
	virtual void HandleHearingLocations(const FVector& vecHearingLocation);
	virtual void HandleTeamActors(AActor* OtherActor);

	
private:

	UPROPERTY()
	Amob_base* pBase_Mob;
	UPROPERTY()
	AActor* TargetActor;
	
	uint8 TeamID;
	FVector ReceiveLocation;

	double flradius_sight;
	double flradius_hearing;
	bool blsMatchedSense;	
};
