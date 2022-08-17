#pragma once


#include "Room/Room.h"
#include "FRoomStruct.generated.h"


USTRUCT(BlueprintType)
struct FRoomStruct
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int GenerationStep;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ARoom* RoomReference;
};
