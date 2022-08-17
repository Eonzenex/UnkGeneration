// Fill out your copyright notice in the Description page of Project Settings.


#include "Zone/ZoneComponent.h"

#include "Misc/UnkGenUtils.h"
#include "Kismet/GameplayStatics.h"


UZoneComponent::UZoneComponent() : Super()
{
	SetIsReplicatedByDefault(true);
	
	ZoneType = EZone::Z_None;
	CellDimensionsInMeters = FVector(30.f, 30.f, 30.f);
	LocationInCells = FVector3i::Zero();
	ZoneSizeInCells = FVector2i(17, 17);
	RNG = FRandomStream(0);

	GridRooms = TMap<int, FCellInformation>();

	ZoneRoomGenerationSettings = FZoneRoomGenerationSettings();
	ZoneRoomHandle = FDataTableRowHandle();
	ZoneRoomHandle.RowName = FName(TEXT("ResearchZone"));

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ZoneGenerationSettings(TEXT("DataTable'/Game/Placeables/Rooms/DT_ZoneGenerationSettings.DT_ZoneGenerationSettings'"));
	if (DT_ZoneGenerationSettings.Succeeded())
	{
		ZoneRoomHandle.DataTable = DT_ZoneGenerationSettings.Object;
	}
}


void UZoneComponent::GenerateFull_Implementation()
{
	if (!GetOwner()->HasAuthority()) return;
	
	Execute_UnGenerate(this);
	Execute_PreGenerate(this);
	Execute_Generate(this);
	Execute_PostGenerate(this);
}

void UZoneComponent::UnGenerateFull_Implementation()
{
	if (!GetOwner()->HasAuthority()) return;
	
	Execute_UnGenerate(this);
}

void UZoneComponent::UnGenerate_Implementation()
{
	if (!GetOwner()->HasAuthority()) return;
	
	for (const auto& [Coord, Cell] : GridRooms)
	{
		ARoom* Room = Cell.Room;
		if (Room)
		{
			Room->Destroy();
		}
	}

	GridRooms.Empty();

	bAlreadyGenerated = false;
}

void UZoneComponent::PreGenerate_Implementation()
{
	if (!GetOwner()->HasAuthority()) return;
	
	InitCellInfo();
}

void UZoneComponent::PostGenerate_Implementation()
{
	if (!GetOwner()->HasAuthority()) return;
	
	PlaceCells();
}

void UZoneComponent::PostInitProperties()
{
	Super::PostInitProperties();

	if (ZoneRoomHandle.DataTable && ZoneRoomHandle.RowName.IsValid())
	{
		ZoneRoomGenerationSettings = *ZoneRoomHandle.GetRow<FZoneRoomGenerationSettings>("");
	}
}


void UZoneComponent::CountAllInstances(FZoneRoomSizes& ZoneRoomSizes) const
{
	ZoneRoomSizes.Size0Doors = 0;
	ZoneRoomSizes.Size1Door = 0;
	ZoneRoomSizes.Size2Doors = 0;
	ZoneRoomSizes.Size2DoorsCorner = 0;
	ZoneRoomSizes.Size3Doors = 0;
	ZoneRoomSizes.Size4Doors = 0;

	/* Count each room type for placement. */
	for (int x = 0; x < ZoneSizeInCells.X; x++)
	{
		for (int y = 0; y < ZoneSizeInCells.Y; y++)
		{
			const int FlatCoord = UnkGenUtils::CoordsToFlat(x, y, ZoneSizeInCells.X);
			const FCellInformation& CellInfo = GridRooms[FlatCoord];
			if (!CellInfo.bAllocated) continue;
			
			if (CellInfo.CellDoorType == ECellDoor::CD_0Doors)
			{
				ZoneRoomSizes.Size0Doors += 1;
			}
			else if (CellInfo.CellDoorType == ECellDoor::CD_1Door)
			{
				ZoneRoomSizes.Size1Door += 1;
			}
			else if (CellInfo.CellDoorType == ECellDoor::CD_2Doors)
			{
				ZoneRoomSizes.Size2Doors += 1;
			}
			else if (CellInfo.CellDoorType == ECellDoor::CD_2DoorsCorner)
			{
				ZoneRoomSizes.Size2DoorsCorner += 1;
			}
			else if (CellInfo.CellDoorType == ECellDoor::CD_3Doors)
			{
				ZoneRoomSizes.Size3Doors += 1;
			}
			else if (CellInfo.CellDoorType == ECellDoor::CD_4Doors)
			{
				ZoneRoomSizes.Size4Doors += 1;
			}
		}
	}
}

bool UZoneComponent::DoesGenerationSupportMinInstances(const FZoneRoomSizes& ZoneRoomSizes) const
{
	FZoneRoomSizes MinPoolSizes;
	ZoneRoomGenerationSettings.CountMinInstances(MinPoolSizes);

	/* Check each room type supports minimum instance of that room. */
	// if (
	// 	MinPoolSizes.Size0Doors > ZoneRoomSizes.Size0Doors
	// 	|| MinPoolSizes.Size1Door > ZoneRoomSizes.Size1Door
	// 	|| MinPoolSizes.Size2Doors > ZoneRoomSizes.Size2Doors
	// 	|| MinPoolSizes.Size2DoorsCorner > ZoneRoomSizes.Size2DoorsCorner
	// 	|| MinPoolSizes.Size3Doors > ZoneRoomSizes.Size3Doors
	// 	|| MinPoolSizes.Size4Doors > ZoneRoomSizes.Size4Doors
	// ) {
	// 	UnkGenUtils::Log(FString::Printf(TEXT("UZoneComponent::DoesGenerationSupportMinInstances - Minimum instances not supported for generation size.")));
	// 	return false;
	// }

	if (MinPoolSizes.Size0Doors > ZoneRoomSizes.Size0Doors)
	{
		UnkGenUtils::Log(FString::Printf(TEXT("UZoneComponent::DoesGenerationSupportMinInstances - Size0Doors Minimum instances not supported for generation size.")));
		return false;
	}

	if (MinPoolSizes.Size1Door > ZoneRoomSizes.Size1Door)
	{
		UnkGenUtils::Log(FString::Printf(TEXT("UZoneComponent::DoesGenerationSupportMinInstances - Size1Door Minimum instances not supported for generation size.")));
		return false;
	}

	if (MinPoolSizes.Size2Doors > ZoneRoomSizes.Size2Doors)
	{
		UnkGenUtils::Log(FString::Printf(TEXT("UZoneComponent::DoesGenerationSupportMinInstances - Size2Doors Minimum instances not supported for generation size.")));
		return false;
	}

	if (MinPoolSizes.Size3Doors > ZoneRoomSizes.Size3Doors)
	{
		UnkGenUtils::Log(FString::Printf(TEXT("UZoneComponent::DoesGenerationSupportMinInstances - Size3Doors Minimum instances not supported for generation size.")));
		return false;
	}

	if (MinPoolSizes.Size4Doors > ZoneRoomSizes.Size4Doors)
	{
		UnkGenUtils::Log(FString::Printf(TEXT("UZoneComponent::DoesGenerationSupportMinInstances - Size4Doors Minimum instances not supported for generation size.")));
		return false;
	}

	return true;
}


void UZoneComponent::InitCellInfo()
{
	GridRooms = TMap<int, FCellInformation>();
	GridRooms.Reserve(ZoneSizeInCells.X * ZoneSizeInCells.Y);

	// Mark edges and corners
	for (int x = 0; x < ZoneSizeInCells.X; x++)
	{
		const int FlatCoord0 = UnkGenUtils::CoordsToFlat(x, 0, ZoneSizeInCells.X);
		const int FlatCoordX = UnkGenUtils::CoordsToFlat(x, ZoneSizeInCells.Y-1, ZoneSizeInCells.X);

		ECellEdge EdgeType = ECellEdge::CE_Wall;
		if (x == 0 || x == ZoneSizeInCells.X-1)
		{
			EdgeType = ECellEdge::CE_Corner;
		}
		
		GridRooms.Emplace(FlatCoord0, FCellInformation(EdgeType));
		GridRooms.Emplace(FlatCoordX, FCellInformation(EdgeType));
	}

	for (int y = 0; y < ZoneSizeInCells.Y; y++)
	{
		const int FlatCoord0 = UnkGenUtils::CoordsToFlat(0, y, ZoneSizeInCells.X);
		const int FlatCoordY = UnkGenUtils::CoordsToFlat(ZoneSizeInCells.Y-1, y, ZoneSizeInCells.X);

		ECellEdge EdgeType = ECellEdge::CE_Wall;
		if (y == 0 || y == ZoneSizeInCells.Y-1)
		{
			EdgeType = ECellEdge::CE_Corner;
		}
		
		GridRooms.Emplace(FlatCoord0, FCellInformation(EdgeType));
		GridRooms.Emplace(FlatCoordY, FCellInformation(EdgeType));
	}

	// Fill rest as normal
	for (int x = 1; x < ZoneSizeInCells.X - 1; x++)
	{
		for (int y = 1; y < ZoneSizeInCells.Y - 1; y++)
		{
			const int FlatCoord = UnkGenUtils::CoordsToFlat(x, y, ZoneSizeInCells.X);
			GridRooms.Emplace(FlatCoord, FCellInformation(ECellEdge::CE_Middle));
		}
	}
}

void UZoneComponent::CalcCellDoors()
{
	for (int x = 0; x < ZoneSizeInCells.X; x++)
	{
		for (int y = 0; y < ZoneSizeInCells.Y; y++)
		{
			const int FlatCoord = UnkGenUtils::CoordsToFlat(x, y, ZoneSizeInCells.X);
			const FCellInformation& CellInfo = GridRooms[FlatCoord];
			if (!CellInfo.bAllocated) continue;

			bool bCheckUp = true;
			bool bCheckDown = true;
			bool bCheckLeft = true;
			bool bCheckRight = true;
			
			if (x == 0) bCheckDown = false;
			if (x == ZoneSizeInCells.X - 1) bCheckUp = false;
			if (y == 0) bCheckLeft = false;
			if (y == ZoneSizeInCells.Y - 1) bCheckRight = false;

			bool bUpAllocated, bDownAllocated, bLeftAllocated, bRightAllocated;
			bUpAllocated = bDownAllocated = bLeftAllocated = bRightAllocated = false;
			
			int DoorCount = 0;
			if (bCheckUp)
			{
				const int ThisFlatCoord = UnkGenUtils::CoordsToFlat(x + 1, y, ZoneSizeInCells.X);
				if (GridRooms[ThisFlatCoord].bAllocated)
				{
					bUpAllocated = true;
					DoorCount++;
				}
			}
			if (bCheckDown)
			{
				const int ThisFlatCoord = UnkGenUtils::CoordsToFlat(x - 1, y, ZoneSizeInCells.X);
				if (GridRooms[ThisFlatCoord].bAllocated)
				{
					bDownAllocated = true;
					DoorCount++;
				}
			}
			if (bCheckLeft)
			{
				const int ThisFlatCoord = UnkGenUtils::CoordsToFlat(x, y - 1, ZoneSizeInCells.X);
				if (GridRooms[ThisFlatCoord].bAllocated)
				{
					bLeftAllocated = true;
					DoorCount++;
				}
			}
			if (bCheckRight)
			{
				const int ThisFlatCoord = UnkGenUtils::CoordsToFlat(x, y + 1, ZoneSizeInCells.X);
				if (GridRooms[ThisFlatCoord].bAllocated)
				{
					bRightAllocated = true;
					DoorCount++;
				}
			}

			ECellDoor DoorType = ECellDoor::CD_4Doors;
			ERotateAngle RotationAngle = ERotateAngle::RA_0;
			if (DoorCount == 3)
			{
				DoorType = ECellDoor::CD_3Doors;
				if (!bUpAllocated) RotationAngle = ERotateAngle::RA_90;
				if (!bRightAllocated) RotationAngle = ERotateAngle::RA_180;
				if (!bDownAllocated) RotationAngle = ERotateAngle::RA_270;
			}
			else if (DoorCount == 2)
			{
				if (bUpAllocated && bDownAllocated)
				{
					DoorType = ECellDoor::CD_2Doors;
					RotationAngle = ERotateAngle::RA_0;
				}
				else if (bLeftAllocated && bRightAllocated)
				{
					DoorType = ECellDoor::CD_2Doors;
					RotationAngle = ERotateAngle::RA_90;
				}
				
				else if (bUpAllocated && bRightAllocated)
				{
					DoorType = ECellDoor::CD_2DoorsCorner;
					RotationAngle = ERotateAngle::RA_0;
				}
				else if (bRightAllocated && bDownAllocated)
				{
					DoorType = ECellDoor::CD_2DoorsCorner;
					RotationAngle = ERotateAngle::RA_90;
				}
				else if (bDownAllocated && bLeftAllocated)
				{
					DoorType = ECellDoor::CD_2DoorsCorner;
					RotationAngle = ERotateAngle::RA_180;
				}
				else if (bLeftAllocated && bUpAllocated)
				{
					DoorType = ECellDoor::CD_2DoorsCorner;
					RotationAngle = ERotateAngle::RA_270;
				}
			}
			else if (DoorCount == 1)
			{
				DoorType = ECellDoor::CD_1Door;
				if (bRightAllocated) RotationAngle = ERotateAngle::RA_90;
				if (bDownAllocated) RotationAngle = ERotateAngle::RA_180;
				if (bLeftAllocated) RotationAngle = ERotateAngle::RA_270;
			}

			GridRooms[FlatCoord].CellDoorType = DoorType;
			GridRooms[FlatCoord].RotationAngle = RotationAngle;
		}
	}
}

void UZoneComponent::PlaceCells()
{
	FZoneRoomSizes ZoneRoomSizes;
	CountAllInstances(ZoneRoomSizes);
	
	if (!DoesGenerationSupportMinInstances(ZoneRoomSizes))
	{
		UnkGenUtils::Log(FString::Printf(TEXT("UZoneComponent::PlaceCells - Minimum size was too big")));
		return;
	}

	FZoneRoomPools ZoneRoomPools;
	ZoneRoomGenerationSettings.GetAllInstances(RNG, ZoneRoomPools, ZoneRoomSizes);
	
	// Place allocated cells
	for (int x = 0; x < ZoneSizeInCells.X; x++)
	{
		for (int y = 0; y < ZoneSizeInCells.Y; y++)
		{
			const int FlatCoord = UnkGenUtils::CoordsToFlat(x, y, ZoneSizeInCells.X);
			FCellInformation& CellInfo = GridRooms[FlatCoord];
			if (!CellInfo.bAllocated) continue;

			const FVector Location = UnkGenUtils::MapGridToRelativeLocation(
				(-ZoneSizeInCells.X / 2) + x,
				(-ZoneSizeInCells.Y / 2) + y,
				CellDimensionsInMeters,
				LocationInCells.Z
			);
			
			FRotator Rotation = FRotator::ZeroRotator;
			if (CellInfo.RotationAngle == ERotateAngle::RA_90) Rotation = FRotator(0, 90, 0);
			if (CellInfo.RotationAngle == ERotateAngle::RA_180) Rotation = FRotator(0, 180, 0);
			if (CellInfo.RotationAngle == ERotateAngle::RA_270) Rotation = FRotator(0, 270, 0);

			if (CellInfo.CellDoorType == ECellDoor::CD_None)
			{
				UnkGenUtils::Log(FString::Printf(TEXT("UZoneComponent::PlaceCells - CellDoorType was CD_None")));
				continue;
			}
			
			TSubclassOf<ARoom> RoomClass = ZoneRoomPools.GetRoom(RNG, CellInfo.CellDoorType);
			if (!RoomClass)
			{
				// UnkUtils::Log(FString::Printf(TEXT("UZoneComponent::PlaceCells - RoomClass was NONE"), CellInfo.CellDoorType));
				continue;
			}
			
			CellInfo.Room = GetWorld()->SpawnActor<ARoom>(RoomClass, Location, Rotation);
		}
	}

	GridRooms.KeySort([](int A, int B) {
		return A < B;
	});
	
	OnLevelFullyLoadedEvent.Broadcast();
}

void UZoneComponent::AllocateHallway(const int X, const int Y, const int Length, const int GenerationStep, const bool bHorizontal)
{
	const int SafeX = FMath::Clamp(X, 0, ZoneSizeInCells.X - 1);
	const int SafeY = FMath::Clamp(Y, 0, ZoneSizeInCells.Y - 1);

	if (bHorizontal)
	{
		const int SafeYMax = FMath::Clamp(SafeY + Length, 0, ZoneSizeInCells.Y);
		for (int y = SafeY; y < SafeYMax; y++)
		{
			const int FlatCoord = UnkGenUtils::CoordsToFlat(SafeX, y, ZoneSizeInCells.X);
			GridRooms[FlatCoord].bAllocated = true;
			GridRooms[FlatCoord].GenerationStep = GenerationStep;
		}
		
		return;
	}

	const int SafeXMax = FMath::Clamp(SafeX + Length, 0, ZoneSizeInCells.X);
	for (int x = SafeX; x < SafeXMax; x++)
	{
		const int FlatCoord = UnkGenUtils::CoordsToFlat(x, SafeY, ZoneSizeInCells.X);
		GridRooms[FlatCoord].bAllocated = true;
		GridRooms[FlatCoord].GenerationStep = GenerationStep;
	}
}
