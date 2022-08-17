#pragma once

#include "ERotateAngle.generated.h"


UENUM(BlueprintType)
enum class ERotateAngle : uint8
{
	RA_0	= 0 UMETA(DisplayName = "0 degrees"),
	RA_90	= 1 UMETA(DisplayName = "90 degrees"),
	RA_180	= 2 UMETA(DisplayName = "180 degrees"),
	RA_270	= 3 UMETA(DisplayName = "270 degrees"),
};
