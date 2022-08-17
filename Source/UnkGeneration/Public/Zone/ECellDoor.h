#pragma once

#include "ECellDoor.generated.h"


UENUM(BlueprintType)
enum class ECellDoor : uint8
{
	CD_None			 = 0 UMETA(DisplayName = "None"),
	CD_0Doors		 = 1 UMETA(DisplayName = "0 Door"),
	CD_1Door		 = 2 UMETA(DisplayName = "1 Door"),
	CD_2Doors		 = 3 UMETA(DisplayName = "2 Doors"),
	CD_2DoorsCorner	 = 4 UMETA(DisplayName = "2 Doors (Corner)"),
	CD_3Doors		 = 5 UMETA(DisplayName = "3 Doors"),
	CD_4Doors		 = 6 UMETA(DisplayName = "4 Doors")
};
