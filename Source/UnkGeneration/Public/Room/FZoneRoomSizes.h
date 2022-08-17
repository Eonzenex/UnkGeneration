// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FZoneRoomSizes.generated.h"


USTRUCT(BlueprintType)
struct UNKGENERATION_API FZoneRoomSizes
{
	GENERATED_BODY(BlueprintType)
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Size0Doors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Size1Door;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Size2Doors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Size2DoorsCorner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Size3Doors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Size4Doors;


	FZoneRoomSizes(
		const int Size0Doors,
		const int Size1Door,
		const int Size2Doors,
		const int Size2DoorsCorner,
		const int Size3Doors,
		const int Size4Doors
	) :
		Size0Doors(Size0Doors),
		Size1Door(Size1Door),
		Size2Doors(Size2Doors),
		Size2DoorsCorner(Size2DoorsCorner),
		Size3Doors(Size3Doors),
		Size4Doors(Size4Doors)
	{}

	FZoneRoomSizes()
	: FZoneRoomSizes(0, 0, 0, 0, 0, 0)
	{}
};