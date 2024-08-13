#pragma once

#include "ESense.h"
#include "../../../../../UE5/UE_5.4/Engine/Source/Runtime/Core/Public/HAL/Platform.h"

// for perception component
enum class ESenseConfig : uint8
{
	NONE = 0x01,
	SIGHT = 0x02,
	HEARING = 0x04,
	DAMAGE = 0x08,
	TEAM = 0x10,
};
