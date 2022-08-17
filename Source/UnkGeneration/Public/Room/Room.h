// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Misc/Power/PowerInterface.h"
#include "Room.generated.h"


UCLASS(Blueprintable, BlueprintType)
class UNKGENERATION_API ARoom : public AStaticMeshActor, public IPowerInterface
{
	GENERATED_BODY()
	
public:
	ARoom();
};
