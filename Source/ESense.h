#pragma once

#include "ESense.h"
#include "../../../../../UE5/UE_5.4/Engine/Source/Runtime/Core/Public/HAL/Platform.h"

// for perception component
enum class ESenseConfig : uint8
{
	SIGHT,
	HEARING,
	DAMAGE,
	TEAM,
};
