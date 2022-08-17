// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FVector3i.generated.h"


USTRUCT(BlueprintType)
struct UNKGENERATION_API FVector3i
{
	GENERATED_BODY()
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int X;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Y;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Z;


	static FVector3i Zero()
	{
		return FVector3i();
	}


	FVector3i() : X(0), Y(0), Z(0)
	{}
	
	FVector3i(
		const int X,
		const int Y,
		const int Z
	) : X(X), Y(Y), Z(Z)
	{}
};