// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FRoomVariationGenerationSettings.h"
#include "Engine/DataTable.h"
#include "Misc/UnkGenUtils.h"
#include "FRoomGenerationSettings.generated.h"


USTRUCT(BlueprintType)
struct UNKGENERATION_API FRoomGenerationSettings : public FTableRowBase
{
	GENERATED_BODY()

	/* Different variations of the room to pick. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomVariationGenerationSettings> Variations;

	/* Weight of this room. More weight will increase the chances of spawning this room. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=1))
	int Weight;

	/* Minimum number of rooms to place. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0))
	int MinInstances;

	/* Current number of times this room was placed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0))
	int Instances;

	/* Maximum number of rooms to place. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=1))
	int MaxInstances;

	
	/* Whether or not we still need to place the minimum number of instances for this room. */
	bool NeedsMinVariation() const
	{
		if (Variations.Num() == 0) return false;

		return Instances < MinInstances;
	}

	/* Whether or not we still need to place the minimum number of instances for this room. */
	static bool NeedsMinVariation(const TArray<FRoomGenerationSettings>& Rooms)
	{
		if (Rooms.Num() == 0) return false;

		for (const FRoomGenerationSettings& Room : Rooms)
		{
			if (Room.Instances < Room.MinInstances)
			{
				return true;
			}
		}
		
		return false;
	}
	
	/* Count the minimum number of instances of a room. */
	static int CountMinInstances(const TArray<FRoomGenerationSettings>& Variations)
	{
		int Count = 0;
		for (const FRoomGenerationSettings& Variation : Variations)
		{
			Count += Variation.MinInstances;
		}

		return Count;
	}
	
	/* Whether or not we can still place instances for this room. */
	bool CanGetVariation() const
	{
		if (Variations.Num() == 0) return false;

		return Instances < MaxInstances;
	}
	
	/* Get a variation. */
	TSubclassOf<ARoom> GetVariation(const FRandomStream& RNG)
	{
		if (Variations.Num() == 0)
		{
			UnkGenUtils::Log(FString::Printf(TEXT("FRoomGenerationSettings::GetVariation - Variations size was 0")));
			return nullptr;
		}
		
		if (Instances >= MaxInstances)
		{
			UnkGenUtils::Log(FString::Printf(TEXT("FRoomGenerationSettings::GetVariation - Too many instances")));
			return nullptr;
		}
		
		int RoomWeightMax = 0;
		for (const auto& Variation : Variations)
		{
			RoomWeightMax += Variation.Weight;
		}

		int RoomValue = RNG.RandRange(0, RoomWeightMax);
		while (true)
		{
			for (const FRoomVariationGenerationSettings& Variation : Variations)
			{
				RoomValue -= Variation.Weight;
				if (RoomValue <= 0)
				{
					Instances += 1;
					return Variation.Class;
				}
			}
		}
	}

	
	FRoomGenerationSettings(
		const TArray<FRoomVariationGenerationSettings>& Variations,
		const int Weight,
		const int MinInstances,
		const int Instances,
		const int MaxInstances
	) :
		Variations(Variations),
		Weight(Weight),
		MinInstances(MinInstances),
		Instances(Instances),
		MaxInstances(MaxInstances)
	{}

	FRoomGenerationSettings(
		const TArray<FRoomVariationGenerationSettings>& Variations,
		const int Weight,
		const int MinInstances,
		const int MaxInstances
	) : FRoomGenerationSettings(Variations, Weight, MinInstances, 0, MaxInstances)
	{}

	FRoomGenerationSettings(
		const TArray<FRoomVariationGenerationSettings>& Variations,
		const int Weight
	) : FRoomGenerationSettings(Variations, Weight, 0, 20)
	{}

	explicit FRoomGenerationSettings(const TArray<FRoomVariationGenerationSettings>& Variations)
		: FRoomGenerationSettings(Variations, 100)
	{}

	FRoomGenerationSettings()
	: FRoomGenerationSettings(
		TArray<FRoomVariationGenerationSettings>(),
		100, 1, 0, 20
	) {}
};