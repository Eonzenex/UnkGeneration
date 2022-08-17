// Copyright Epic Games, Inc. All Rights Reserved.

#include "Misc/UnkGenUtils.h"
#include "Zone/FRoomWeight.h"


int UnkGenUtils::CoordsToFlat(const int X, const int Y, const int SizeX)
{
	return X + Y * SizeX;
}

void UnkGenUtils::Log(const FString& Message, const FColor& Color)
{
	// UE_LOG(UnkDefault, Log, TEXT("%s"), *Message);

	if (bDisplayLog) GEngine->AddOnScreenDebugMessage(-1, 4.f, Color, Message);
}

FVector UnkGenUtils::MapGridToRelativeLocation(const int X, const int Y, const FVector CellSizeMeters, const int Z)
{
	const FVector CellSizeCm = CellSizeMeters * 100.f;
	const FVector Location = FVector(X * CellSizeCm.X, Y * CellSizeCm.Y, Z * CellSizeCm.Z);
	return Location;
}

TSubclassOf<ARoom> UnkGenUtils::GetRoomType(const TArray<FRoomWeight>& RoomWeights, FRandomStream& RNG)
{
	if (RoomWeights.Num() == 0) return nullptr;
	
	int RoomWeightMax = 0;
	for (const auto& [Weight, Room] : RoomWeights)
	{
		RoomWeightMax += Weight;
	}

	int RoomValue = RNG.RandRange(0, RoomWeightMax);
	while (true)
	{
		for (const auto& [Weight, Room] : RoomWeights)
		{
			RoomValue -= Weight;
			if (RoomValue <= 0)
			{
				return Room;
			}
		}
	}
}
