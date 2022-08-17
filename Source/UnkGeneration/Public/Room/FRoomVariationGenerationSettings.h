// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Room.h"
#include "Engine/DataTable.h"
#include "FRoomVariationGenerationSettings.generated.h"


USTRUCT(BlueprintType)
struct UNKGENERATION_API FRoomVariationGenerationSettings : public FTableRowBase
{
	GENERATED_BODY()

	/* The room class to spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARoom> Class;

	/* Weight of this room. More weight will increase the chances of spawning this room. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=1))
	int Weight;

	FRoomVariationGenerationSettings(
		const TSubclassOf<ARoom> Class, 
		const int Weight
	) :
		Class(Class),
		Weight(Weight)
	{}

	explicit FRoomVariationGenerationSettings(const TSubclassOf<ARoom> Class) :
		Class(Class),
		Weight(100)
	{}

	FRoomVariationGenerationSettings()
	: FRoomVariationGenerationSettings(ARoom::StaticClass(), 100) {}
};