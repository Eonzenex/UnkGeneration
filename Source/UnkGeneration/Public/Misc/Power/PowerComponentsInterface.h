// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EPowerStatus.h"
#include "UObject/Interface.h"
#include "PowerComponentsInterface.generated.h"


UINTERFACE(BlueprintType)
class UNKGENERATION_API UPowerComponentsInterface : public UInterface
{
	GENERATED_BODY()
};


class UNKGENERATION_API IPowerComponentsInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="PowerComponentsInterface")
	void GetPowerActors(TArray<AActor*>& OutActors);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="PowerComponentsInterface")
	void GetPowerActorComponents(TArray<UActorComponent*>& OutComponents);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="PowerComponentsInterface")
	void SetPowerStatus(const EPowerStatus PowerStatus);
};