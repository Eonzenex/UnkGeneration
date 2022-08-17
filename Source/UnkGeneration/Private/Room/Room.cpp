// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/Room.h"


ARoom::ARoom() : Super()
{
	bReplicates = true;
	bNetLoadOnClient = true;
	bAlwaysRelevant = true;
	MinNetUpdateFrequency = 0.5f;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	GetStaticMeshComponent()->SetMobility(EComponentMobility::Static);
	GetStaticMeshComponent()->SetSimulatePhysics(false);
}
