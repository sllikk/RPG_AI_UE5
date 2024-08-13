// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_CORE/Public/EntityBrain//base_controller_mobs.h"

#include <iostream>

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Team.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Sight.h"

Abase_controller_mobs::Abase_controller_mobs(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.Get()), pConfig_Sight(nullptr), pConfig_Damage(nullptr), pConfig_Team(nullptr),
	  pBase_Mob(nullptr), TargetActor(nullptr) ,TeamID(0), ReceiveLocation(FVector::ZeroVector), flradius_sight(1000), flradius_hearing(500)
{
	SetPerceptionComponent(*ObjectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("MOBS_PERCEPTION")));

	pConfig_Sight = ObjectInitializer.CreateDefaultSubobject<UAISenseConfig_Sight>(this, TEXT("MOBS_SIGHT"));
	pConfig_Damage= ObjectInitializer.CreateDefaultSubobject<UAISenseConfig_Damage>(this, TEXT("MOBS_DAMAGE"));
	pConfig_Hearing = ObjectInitializer.CreateDefaultSubobject<UAISenseConfig_Hearing>(this, TEXT("MOBS_HEARING"));
	pConfig_Team = ObjectInitializer.CreateDefaultSubobject<UAISenseConfig_Team>(this, TEXT("MOBS_TEAM"));
	BBC = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("MOBS_BBC"));
	BTC = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("MOBS_BTC"));
	
	// Setting Sense
	pConfig_Sight->SightRadius = flradius_sight;
	pConfig_Sight->LoseSightRadius = flradius_sight + 155.0f;
	pConfig_Sight->PeripheralVisionAngleDegrees = 90.0f;
	pConfig_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	pConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	pConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	pConfig_Sight->SetMaxAge(10.0f);

	pConfig_Hearing->HearingRange = flradius_hearing;
	pConfig_Hearing->DetectionByAffiliation.bDetectFriendlies = false;
	pConfig_Hearing->DetectionByAffiliation.bDetectEnemies = true;
	pConfig_Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	pConfig_Hearing->SetMaxAge(3.0f);
	
	
	PerceptionComponent->SetDominantSense(*pConfig_Sight->Implementation);
	PerceptionComponent->ConfigureSense(*pConfig_Sight);
	PerceptionComponent->ConfigureSense(*pConfig_Team);
	PerceptionComponent->ConfigureSense(*pConfig_Hearing);
	PerceptionComponent->ConfigureSense(*pConfig_Damage);
}

void Abase_controller_mobs::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void Abase_controller_mobs::BeginPlay()
{
	Super::BeginPlay();

	UAIPerceptionSystem::GetCurrent(GetWorld())->UpdateListener(*GetPerceptionComponent());
}

void Abase_controller_mobs::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	pBase_Mob = Cast<Amob_base>(InPawn);
	if (pBase_Mob != nullptr)
	{
		check(PerceptionComponent != nullptr)
		PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &Abase_controller_mobs::UpdatePerception);

		if (pBase_Mob->GetBehaviorTree().IsPending())
		{
			UBehaviorTree* BehaviorTree = pBase_Mob->GetBehaviorTree().LoadSynchronous();
			if (BehaviorTree != nullptr)
			{
				BTC->StartTree(*BehaviorTree);
				BBC->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
			}
		}
		
	}
	
}

ETeamAttitude::Type Abase_controller_mobs::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();

			if (OtherTeamID == TeamID)
			{
				return ETeamAttitude::Friendly;
			}
			// alliance teams
			if (OtherTeamID == 10){

				return ETeamAttitude::Neutral;
			}
		}
	}
	return ETeamAttitude::Hostile;

}

FGenericTeamId Abase_controller_mobs::GetGenericTeamId() const
{
	return TeamID;
}

void Abase_controller_mobs::UpdatePerception(const TArray<AActor*>& UpdateActors)
{
	for (AActor* TargetActors : UpdateActors)
	{
		FAIStimulus ActorStimulus;

		if (CanSenseActors(TargetActors, ESenseConfig::SIGHT, ActorStimulus))
		{
			UE_LOG(LogAIPerception, Warning, TEXT("SIGHT"))
			HandleSightActors(TargetActors);
		}
		else
		{
			UE_LOG(LogAIPerception, Warning, TEXT("SIGHT LOST"))
			HandleSightLostActors(TargetActors);
		}

		if (CanSenseActors(TargetActors, ESenseConfig::HEARING, ActorStimulus))
		{
			UE_LOG(LogAIPerception, Warning, TEXT("HEARING"))
			HandleHearingLocations(ActorStimulus.StimulusLocation);			
		}

		if (CanSenseActors(TargetActors, ESenseConfig::DAMAGE, ActorStimulus))
		{
			UE_LOG(LogAIPerception, Warning, TEXT("DAMAGE"))
			HandleDamageActors(TargetActors);
		}
	}
/*
	
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
		ETeamAttitude::Type TeamAttitude = GetTeamAttitudeTowards(*OtherActors);	
		FString strDebug;

		switch (TeamAttitude)
		{
		case ETeamAttitude::Hostile:  
			strDebug = TEXT("Hostile");
			break;	
		case ETeamAttitude::Friendly:	
			strDebug = TEXT("Friendly");
			break;
		case ETeamAttitude::Neutral:	
			strDebug = TEXT("Neutral");
			break;
		default:
			break;
		}
		UE_LOG(LogAIPerception, Warning, TEXT("STIMULUS: %s, TEAM: %s"), *OtherActors->GetName(), *strDebug);
#endif
*/
}

bool Abase_controller_mobs::CanSenseActors(AActor* SenseActor, ESenseConfig SenseConfig, FAIStimulus& Stimulus)
{
	FActorPerceptionBlueprintInfo ActorPerceptionBlueprintInfo;
	if (PerceptionComponent->GetActorsPerception(SenseActor, ActorPerceptionBlueprintInfo))
	{
		for (const FAIStimulus& CurrentStimulus : ActorPerceptionBlueprintInfo.LastSensedStimuli)
		{
			TSubclassOf<UAISense> SensesClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), CurrentStimulus);
			bool blsMatchedSense = false;

			if (SensesClass != nullptr)
			{
				switch (SenseConfig)
				{
				case ESenseConfig::NONE:	
					break;

				case ESenseConfig::SIGHT:
				if (SensesClass == UAISense_Sight::StaticClass())
				{
					blsMatchedSense = true;
				}	
					break;
				case ESenseConfig::HEARING:
					if (SensesClass == UAISense_Hearing::StaticClass())
					{
						blsMatchedSense = true;
					}	
					break;
				case ESenseConfig::DAMAGE:
					if (SensesClass == UAISense_Damage::StaticClass())
					{
						blsMatchedSense = true;
					}	
					break;
				case ESenseConfig::TEAM:
					if (SensesClass == UAISense_Team::StaticClass())
					{
						blsMatchedSense = true;
					}	
					break;
					default: UE_LOG(LogAIPerception, Error, TEXT("No Special Sense"))
				}
				if (blsMatchedSense)
				{
					Stimulus = CurrentStimulus;
					return Stimulus.WasSuccessfullySensed();
				}
			}
		}
	}

	return false;
}

void Abase_controller_mobs::HandleSightActors(AActor* OtherActor)
{

}

void Abase_controller_mobs::HandleSightLostActors(AActor* OtherActor)
{

}

void Abase_controller_mobs::HandleDamageActors(AActor* OtherActor)
{

}

void Abase_controller_mobs::HandleHearingLocations(const FVector& vecHearingLocation)
{

}

void Abase_controller_mobs::HandleTeamActors(AActor* OtherActor)
{

}
