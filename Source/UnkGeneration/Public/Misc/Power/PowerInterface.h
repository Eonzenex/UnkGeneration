// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EPowerStatus.h"
#include "UObject/Interface.h"
#include "PowerInterface.generated.h"


UINTERFACE(BlueprintType)
class UNKGENERATION_API UPowerInterface : public UInterface
{
	GENERATED_BODY()
};


class UNKGENERATION_API IPowerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="PowerInterface")
	float GetPower() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="PowerInterface")
	float GetMaxPower() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="PowerInterface")
	EPowerStatus GetPowerStatus() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="PowerInterface")
	void SetPowerStatus(const EPowerStatus NewValue);
};