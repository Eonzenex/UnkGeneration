// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/RandomStream.h"

#include "EZone.h"
#include "FCellInformation.h"
#include "GenerateInterface.h"
#include "Engine/DataTable.h"
#include "Misc/FVector2i.h"
#include "Misc/FVector3i.h"
#include "Room/FZoneRoomGenerationSettings.h"
#include "ZoneComponent.generated.h"


class ADoor;


UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class UNKGENERATION_API UZoneComponent : public UActorComponent, public IGenerateInterface
{
	GENERATED_BODY()

public:
	UZoneComponent();

#pragma region Getters
	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	FVector3i GetLocationInCells() const { return LocationInCells; }

	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	FVector2i GetZoneSizeInCells() const { return ZoneSizeInCells; }
	
	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	FRandomStream GetRNG() const { return RNG; }

	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	FVector GetCellDimensionsInMeters() const { return CellDimensionsInMeters; }
#pragma endregion

#pragma region Setters
	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	void SetLocationInCells(const FVector3i& NewValue) { LocationInCells = NewValue; }

	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	void SetZoneSizeInCells(const FVector2i& NewValue) { ZoneSizeInCells = NewValue; }
	
	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	void SetRNG(const FRandomStream& NewValue) { RNG = NewValue; }
#pragma endregion

#pragma region Events
	DECLARE_EVENT(UZoneComponent, FOnLevelFullyLoadedEvent)
	FOnLevelFullyLoadedEvent& GetOnLevelFullyLoaded() { return OnLevelFullyLoadedEvent; }
#pragma endregion
	
	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	void AllocateHallway(const int X, const int Y, const int Length, const int GenerationStep, const bool bHorizontal = true);

	virtual void GenerateFull_Implementation() override;
	virtual void UnGenerateFull_Implementation() override;
	virtual void PreGenerate_Implementation() override;
	virtual void PostGenerate_Implementation() override;
	virtual void UnGenerate_Implementation() override;
	
	virtual void PostInitProperties() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ZoneComponent")
	EZone ZoneType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZoneComponent")
	FVector CellDimensionsInMeters;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZoneComponent")
	FVector3i LocationInCells;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZoneComponent")
	FVector2i ZoneSizeInCells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZoneComponent")
	FRandomStream RNG;

#pragma region Rooms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZoneComponent|Rooms")
	FZoneRoomGenerationSettings ZoneRoomGenerationSettings;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(RowType=ZoneRoomGenerationSettings), Category="ZoneComponent|Rooms")
	FDataTableRowHandle ZoneRoomHandle;
#pragma endregion
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZoneComponent|References")
	bool bAlreadyGenerated;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ZoneComponent|References")
	TMap<int, FCellInformation> GridRooms;

#pragma region Events
	FOnLevelFullyLoadedEvent OnLevelFullyLoadedEvent;
#pragma endregion
	

	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	void CountAllInstances(FZoneRoomSizes& ZoneRoomSizes) const;
	
	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	bool DoesGenerationSupportMinInstances(const FZoneRoomSizes& ZoneRoomSizes) const;

	
	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	void InitCellInfo();

	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	void CalcCellDoors();
	
	UFUNCTION(BlueprintCallable, Category="ZoneComponent")
	void PlaceCells();
};
