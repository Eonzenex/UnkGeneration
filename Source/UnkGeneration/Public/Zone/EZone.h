#pragma once

#include "EZone.generated.h"


UENUM(BlueprintType)
enum class EZone : uint8
{
	Z_None		UMETA(DisplayName = "None"),
	Z_Research	UMETA(DisplayName = "Research"),
	Z_Ritual	UMETA(DisplayName = "Ritual"),
	Z_Library	UMETA(DisplayName = "Library"),
};
