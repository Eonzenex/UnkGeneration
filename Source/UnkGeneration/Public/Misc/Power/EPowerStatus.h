#pragma once

#include "EPowerStatus.generated.h"


UENUM(BlueprintType)
enum class EPowerStatus : uint8
{
	PS_Off			= 0	UMETA(DisplayName = "Off"),
	PS_TurningOn	= 1	UMETA(DisplayName = "Turning on"),
	PS_On			= 2	UMETA(DisplayName = "Off"),
	PS_TurningOff	= 3	UMETA(DisplayName = "Turning off"),
};
