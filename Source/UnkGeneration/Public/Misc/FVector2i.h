// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FVector2i.generated.h"


USTRUCT(BlueprintType)
struct UNKGENERATION_API FVector2i
{
	GENERATED_BODY()
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int X;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Y;

	
	static FVector2i Zero()
	{
		return FVector2i();
	}

	
	FVector2i() : X(0), Y(0)
	{}
	
	FVector2i(
		const int X,
		const int Y
	) : X(X), Y(Y)
	{}
};