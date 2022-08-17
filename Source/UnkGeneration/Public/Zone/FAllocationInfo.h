#pragma once

#include "Misc/FVector2i.h"

#include "FAllocationInfo.generated.h"


USTRUCT(BlueprintType)
struct UNKGENERATION_API FAllocationInfo
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2i Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2i Length;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int GenerationStep;
	

	FAllocationInfo() :
		Position(0, 0),
		Length(0, 0),
		GenerationStep(0)
	{}

	FAllocationInfo(
		const FVector2i Position,
		const FVector2i Length,
		const int GenerationStep
	) :
		Position(Position),
		Length(Length),
		GenerationStep(GenerationStep)
	{}
};
