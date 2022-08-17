// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Zone/ECellDoor.h"
#include "Zone/ERotateAngle.h"
#include "Zone/FCellInformation.h"


struct FRoomWeight;
class ALevelInstance;


class UNKGENERATION_API UnkGenUtils
{
public:
	static int CoordsToFlat(const int X, const int Y, const int SizeX);

	static inline bool bDisplayLog = true;
	static void Log(const FString& Message, const FColor& Color);
	static void Log(const FString& Message) { Log(Message, FColor::Red); }

	static FVector MapGridToRelativeLocation(const int X, const int Y, const FVector CellSizeMeters, const int Z);
	static TSubclassOf<ARoom> GetRoomType(const TArray<FRoomWeight>& RoomWeights, FRandomStream& RNG);

	static ECellDoor GetCellDoorType(const FCellInformation& CellInfo) { return CellInfo.CellDoorType; }
	static ERotateAngle GetRotationAngle(const FCellInformation& CellInfo) { return CellInfo.RotationAngle; }
};