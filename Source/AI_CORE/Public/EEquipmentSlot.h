#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	NONE		 UMETA(DisplayName = "NONE"),
	SWORD_SLOT   UMETA(DisplayName = "SwordSlot"),
	SHIELD_SLOT  UMETA(DisplayName = "ShieldSlot"),
	MAGIC_SLOT   UMETA(DisplayName = "MagicSlot")

};