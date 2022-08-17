#pragma once


#include "ECellDoor.h"
#include "ECellEdge.h"
#include "ERotateAngle.h"
#include "Engine/LevelStreamingDynamic.h"

#include "FCellInformation.generated.h"


class ARoom;


USTRUCT(BlueprintType)
struct FCellInformation
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECellEdge CellEdge;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECellDoor CellDoorType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int GenerationStep;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERotateAngle RotationAngle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAllocated;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bPlaced;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDoorsPlaced;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ARoom* Room;


	explicit FCellInformation(
		const ECellEdge CellEdgeType = ECellEdge::CE_Middle,
		const ECellDoor CellDoorType = ECellDoor::CD_None,
		const int GenerationStep = 0,
		const ERotateAngle RotationAngle = ERotateAngle::RA_0,
		const bool bValidPosition = false,
		const bool bPlaced = false,
		const bool bDoorsPlaced = false,
		ARoom* Room = nullptr
	) :
		CellEdge(CellEdgeType),
		CellDoorType(CellDoorType),
		GenerationStep(GenerationStep),
		RotationAngle(RotationAngle),
		bAllocated(bValidPosition),
		bPlaced(bPlaced),
		bDoorsPlaced(bDoorsPlaced),
		Room(Room)
	{}
};
