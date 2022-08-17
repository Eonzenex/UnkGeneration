// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FRoomGenerationSettings.h"
#include "FZoneRoomPools.h"
#include "FZoneRoomSizes.h"
#include "Engine/DataTable.h"
#include "FZoneRoomGenerationSettings.generated.h"


USTRUCT(BlueprintType)
struct UNKGENERATION_API FZoneRoomGenerationSettings : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomGenerationSettings> Rooms0Doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomGenerationSettings> Rooms1Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomGenerationSettings> Rooms2Doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomGenerationSettings> Rooms2DoorsCorner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomGenerationSettings> Rooms3Doors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomGenerationSettings> Rooms4Doors;


	/* Count the minimum number of instances. */
	static int CountMinInstances(const TArray<FRoomGenerationSettings>& Rooms)
	{
		int Size = 0;
		for (auto& Room : Rooms)
		{
			Size += Room.MinInstances;
		}

		return Size;
	}
	
	/* Count the minimum number of instances for each room. */
	void CountMinInstances(FZoneRoomSizes& PoolSizes) const
	{
		PoolSizes.Size4Doors = CountMinInstances(Rooms4Doors);
		PoolSizes.Size3Doors = CountMinInstances(Rooms3Doors);
		PoolSizes.Size2Doors = CountMinInstances(Rooms2Doors);
		PoolSizes.Size2Doors = CountMinInstances(Rooms2DoorsCorner);
		PoolSizes.Size1Door = CountMinInstances(Rooms1Door);
		PoolSizes.Size0Doors = CountMinInstances(Rooms0Doors);
	}

	/* Get a variation. */
	static TSubclassOf<ARoom> GetVariation(const FRandomStream& RNG, TArray<FRoomGenerationSettings>& Rooms)
	{
		if (Rooms.Num() == 0) return nullptr;
		
		int RoomWeightMax = 0;
		for (const FRoomGenerationSettings& Room : Rooms)
		{
			if (Room.Instances < Room.MaxInstances) RoomWeightMax += Room.Weight;
		}

		if (RoomWeightMax == 0)
		{
			UnkGenUtils::Log(FString::Printf(TEXT("FZoneRoomGenerationSettings::GetVariation - All rooms exceeded max instances")));
			return nullptr;
		}

		int RoomValue = RNG.RandRange(0, RoomWeightMax);
		while (true)
		{
			for (FRoomGenerationSettings& Room : Rooms)
			{
				RoomValue -= Room.Weight;
				if (RoomValue <= 0)
				{
					const TSubclassOf<ARoom> Result = Room.GetVariation(RNG);
					if (!Result)
					{
						UnkGenUtils::Log(FString::Printf(TEXT("FZoneRoomGenerationSettings::GetVariation - Result was nullptr")));
					}
					return Result;
				}
			}
		}
	}
	
	/* Get a variation. */
	TSubclassOf<ARoom> GetVariation(const FRandomStream& RNG, const ECellDoor DoorType)
	{
		if (DoorType == ECellDoor::CD_4Doors)		return GetVariation(RNG, Rooms4Doors);
		if (DoorType == ECellDoor::CD_3Doors)		return GetVariation(RNG, Rooms3Doors);
		if (DoorType == ECellDoor::CD_2Doors)		return GetVariation(RNG, Rooms2Doors);
		if (DoorType == ECellDoor::CD_2DoorsCorner)	return GetVariation(RNG, Rooms2DoorsCorner);
		if (DoorType == ECellDoor::CD_1Door)		return GetVariation(RNG, Rooms1Door);
		if (DoorType == ECellDoor::CD_0Doors)		return GetVariation(RNG, Rooms0Doors);

		return nullptr;
	}

	/* Gets all variations from the instances yet to reach their minimum placement. */
	static void GetAllMinInstances(const FRandomStream& RNG, TArray<FRoomGenerationSettings>& Rooms, TArray<TSubclassOf<ARoom>>& MinInstances)
	{
		if (Rooms.Num() == 0) return;

		MinInstances.Empty();
		MinInstances.SetNum(0);
		for (auto& Room : Rooms)
		{
			for (int i = 0; i < Room.MinInstances; i++)
			{
				MinInstances.Emplace(Room.GetVariation(RNG));
			}
		}
	}

	/* Gets all variations from the instances yet to reach their minimum placement. */
	static void GetAllInstances(const FRandomStream& RNG, TArray<FRoomGenerationSettings>& Rooms, const int Size, TArray<TSubclassOf<ARoom>>& Instances)
	{
		GetAllMinInstances(RNG, Rooms, Instances);

		const int End = Instances.Num();
		for (int i = End; i < Size; i++)
		{
			const TSubclassOf<ARoom> Result = GetVariation(RNG, Rooms);
			if (!Result)
			{
				UnkGenUtils::Log(FString::Printf(TEXT("FZoneRoomGenerationSettings::GetAllInstances - Result was nullptr")));
			}
			Instances.Emplace(Result);
		}
	}
	
	/* Gets all variations from the instances yet to reach their minimum placement. */
	void GetAllInstances(const FRandomStream& RNG, FZoneRoomPools& ZoneRoomPools, const FZoneRoomSizes& PoolSizes)
	{
		GetAllInstances(RNG, Rooms4Doors, PoolSizes.Size4Doors, ZoneRoomPools.Pool4Doors);
		GetAllInstances(RNG, Rooms3Doors, PoolSizes.Size3Doors, ZoneRoomPools.Pool3Doors);
		GetAllInstances(RNG, Rooms2Doors, PoolSizes.Size2Doors, ZoneRoomPools.Pool2Doors);
		GetAllInstances(RNG, Rooms2DoorsCorner, PoolSizes.Size2DoorsCorner, ZoneRoomPools.Pool2DoorsCorner);
		GetAllInstances(RNG, Rooms1Door, PoolSizes.Size1Door, ZoneRoomPools.Pool1Door);
		GetAllInstances(RNG, Rooms0Doors, PoolSizes.Size0Doors, ZoneRoomPools.Pool0Doors);
	}
	
	/*  */
	void CreateRoomPools(const FRandomStream& RNG, FZoneRoomPools& RoomPools, const FZoneRoomSizes& PoolSizes)
	{
		GetAllInstances(RNG, Rooms4Doors, PoolSizes.Size4Doors, RoomPools.Pool4Doors);
		GetAllInstances(RNG, Rooms3Doors, PoolSizes.Size3Doors, RoomPools.Pool3Doors);
		GetAllInstances(RNG, Rooms2Doors, PoolSizes.Size2Doors, RoomPools.Pool2Doors);
		GetAllInstances(RNG, Rooms2DoorsCorner, PoolSizes.Size2DoorsCorner, RoomPools.Pool2DoorsCorner);
		GetAllInstances(RNG, Rooms1Door, PoolSizes.Size1Door, RoomPools.Pool1Door);
		GetAllInstances(RNG, Rooms0Doors, PoolSizes.Size0Doors, RoomPools.Pool0Doors);
	}
	
	
	FZoneRoomGenerationSettings(
		const TArray<FRoomGenerationSettings> Rooms0Doors,
		const TArray<FRoomGenerationSettings> Rooms1Door,
		const TArray<FRoomGenerationSettings> Rooms2Doors,
		const TArray<FRoomGenerationSettings> Rooms2DoorsCorner,
		const TArray<FRoomGenerationSettings> Rooms3Doors,
		const TArray<FRoomGenerationSettings> Rooms4Doors
	) :
		Rooms0Doors(Rooms0Doors),
		Rooms1Door(Rooms1Door),
		Rooms2Doors(Rooms2Doors),
		Rooms2DoorsCorner(Rooms2DoorsCorner),
		Rooms3Doors(Rooms3Doors),
		Rooms4Doors(Rooms4Doors)
	{}

	FZoneRoomGenerationSettings()
	: FZoneRoomGenerationSettings({}, {}, {}, {}, {}, {})
	{}
};