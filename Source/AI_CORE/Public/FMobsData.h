#pragma once

#include "EEquipmentSlot.h"
#include "NiagaraSystem.h"
#include "Engine/DataTable.h"
#include "FMobsData.generated.h"

USTRUCT(BlueprintType)
struct AI_CORE_API FMobsData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UNiagaraSystem> MobEffect;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UUserWidget> MobWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UClass> ClassEntity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MobMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MobStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxIntelligence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpeedWalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxExperience;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentSlot EquipmentSlot;	
	
	FMobsData(): MobMaxHealth(0), MobStamina(0), MaxIntelligence(0), MaxSpeedWalk(0), MaxExperience(0), EquipmentSlot(EEquipmentSlot::NONE)
	{

	}
};