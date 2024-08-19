// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "weapon_base.generated.h"

class USkeletalMeshComponent;

UCLASS(Blueprintable)
class AI_CORE_API Aweapon_base : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="WeaponMesh", meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* pWeaponMeshComponent;
	
public:	
	// Sets default values for this actor's properties
 	explicit Aweapon_base(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

	
	
};
