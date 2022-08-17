// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Room/Room.h"
#include "Zone/ECellDoor.h"
#include "Misc/UnkGenUtils.h"
#include "FZoneRoomPools.generated.h"


USTRUCT(BlueprintType)
struct UNKGENERATION_API FZoneRoomPools
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> Pool0Doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> Pool1Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> Pool2Doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> Pool2DoorsCorner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> Pool3Doors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> Pool4Doors;

	/* Gets a room from the given pool. */
	static TSubclassOf<ARoom> GetRoom(const FRandomStream& RNG, TArray<TSubclassOf<ARoom>>& Pool)
	{
		if (Pool.Num() == 0)
		{
			UnkGenUtils::Log(FString::Printf(TEXT("FZoneRoomPools::GetRoom - Pool length was 0")));
			return nullptr;
		}
		
		const int Index = RNG.RandRange(0, Pool.Num() - 1);
		const TSubclassOf<ARoom> Result = Pool[Index];
		Pool.RemoveAt(Index, 1);

		if (!Result)
		{
			UnkGenUtils::Log(FString::Printf(TEXT("FZoneRoomPools::GetRoom - Result was nullptr")));
		}

		return Result;
	}

	/* Gets a room. */
	TSubclassOf<ARoom> GetRoom(const FRandomStream& RNG, const ECellDoor RoomType)
	{
		if (RoomType == ECellDoor::CD_0Doors)
		{
			return GetRoom(RNG, Pool0Doors);
		}
		if (RoomType == ECellDoor::CD_1Door)
		{
			return GetRoom(RNG, Pool1Door);
		}
		if (RoomType == ECellDoor::CD_2Doors)
		{
			return GetRoom(RNG, Pool2Doors);
		}
		if (RoomType == ECellDoor::CD_2DoorsCorner)
		{
			return GetRoom(RNG, Pool2DoorsCorner);
		}
		if (RoomType == ECellDoor::CD_3Doors)
		{
			return GetRoom(RNG, Pool3Doors);
		}
		if (RoomType == ECellDoor::CD_4Doors)
		{
			return GetRoom(RNG, Pool4Doors);
		}

		return nullptr;
	}


	FZoneRoomPools(
		const TArray<TSubclassOf<ARoom>> Pool0Doors,
		const TArray<TSubclassOf<ARoom>> Pool1Door,
		const TArray<TSubclassOf<ARoom>> Pool2Doors,
		const TArray<TSubclassOf<ARoom>> Pool2DoorsCorner,
		const TArray<TSubclassOf<ARoom>> Pool3Doors,
		const TArray<TSubclassOf<ARoom>> Pool4Doors
	) :
		Pool0Doors(Pool0Doors),
		Pool1Door(Pool1Door),
		Pool2Doors(Pool2Doors),
		Pool2DoorsCorner(Pool2DoorsCorner),
		Pool3Doors(Pool3Doors),
		Pool4Doors(Pool4Doors)
	{}

	FZoneRoomPools()
	: FZoneRoomPools({}, {}, {}, {}, {}, {}) {}
};
