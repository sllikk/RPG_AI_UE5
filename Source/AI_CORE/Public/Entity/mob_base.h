// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Navigation/CrowdAgentInterface.h"
#include "mob_base.generated.h"

class UNavigationInvokerComponent;
class UWidgetComponent;
class UAIPerceptionStimuliSourceComponent;
class UBehaviorTree;

UCLASS(Blueprintable)
class AI_CORE_API Amob_base : public ACharacter, public ICrowdAgentInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="SENSE",meta=(AllowPrivateAccess = "true"))
	UAIPerceptionStimuliSourceComponent* pPerceptionStimuliSourceComponent;

	UPROPERTY(VisibleAnywhere, Category="NAVIGATION",meta=(AllowPrivateAccess = "true"))
	UNavigationInvokerComponent* pNavigationInvokerComponent;	

	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess = "true"))
	UWidgetComponent* pWidgetComponent;

	UPROPERTY(EditAnywhere, Category="AI", meta=(AllowPrivateAccess = "true"))
	UBehaviorTree* pBehaviorTree;
	
public:
	// Sets default values for this character's properties
	explicit Amob_base(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;
	
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;	

	FORCEINLINE virtual FVector GetCrowdAgentLocation() const override;
	FORCEINLINE virtual FVector GetCrowdAgentVelocity() const override;
	FORCEINLINE virtual void GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const override;
	FORCEINLINE virtual float GetCrowdAgentMaxSpeed() const override;
	FORCEINLINE virtual int32 GetCrowdAgentAvoidanceGroup() const override;
 	FORCEINLINE virtual int32 GetCrowdAgentGroupsToAvoid() const override;
	FORCEINLINE virtual int32 GetCrowdAgentGroupsToIgnore() const override;	
	
public:	

	UBehaviorTree* GetBehaviorTree() const;
	UWidgetComponent* GetWidgetMobs() const;

	float GetHealth() const;
	float GetMaxHealth() const;

	void SetMaxHealth(float flhealth);
	
private:	
	
	float flHealth;
	float flMaxHealth;
	
};


FORCEINLINE UBehaviorTree* Amob_base::GetBehaviorTree() const
{
	return pBehaviorTree;	 
}

FORCEINLINE UWidgetComponent* Amob_base::GetWidgetMobs() const
{
	return pWidgetComponent;
}

FORCEINLINE float Amob_base::GetHealth() const
{
	return flHealth;
}

FORCEINLINE float Amob_base::GetMaxHealth() const
{
	return flMaxHealth;
}


FORCEINLINE void Amob_base::SetMaxHealth(float flhealth)
{
	flMaxHealth = flhealth;	
} 






