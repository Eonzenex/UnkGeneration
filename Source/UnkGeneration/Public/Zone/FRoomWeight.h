#pragma once

#include "Room/Room.h"
#include "FRoomWeight.generated.h"


USTRUCT(BlueprintType)
struct FRoomWeight
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Weight;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ARoom> Room;

	FRoomWeight() :
		Weight(100),
		Room(nullptr)
	{}

	FRoomWeight(
		const int Weight,
		const TSubclassOf<ARoom> Room
	) :
		Weight(Weight),
		Room(Room)
	{}
};
