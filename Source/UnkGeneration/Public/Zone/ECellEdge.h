#pragma once

#include "ECellEdge.generated.h"


UENUM(BlueprintType)
enum class ECellEdge : uint8
{
	CE_Middle	UMETA(DisplayName = "Middle"),
	CE_Wall		UMETA(DisplayName = "Wall"),
	CE_Corner	UMETA(DisplayName = "Corner"),
};
