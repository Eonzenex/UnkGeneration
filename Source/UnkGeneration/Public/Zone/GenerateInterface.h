// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenerateInterface.generated.h"


UINTERFACE(BlueprintType)
class UNKGENERATION_API UGenerateInterface : public UInterface
{
	GENERATED_BODY()
};

class UNKGENERATION_API IGenerateInterface : public IInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="GenerateInterface")
	void PreGenerate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="GenerateInterface")
	void Generate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="GenerateInterface")
	void PostGenerate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="GenerateInterface")
	void UnGenerate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, CallInEditor, Category="GenerateInterface")
	void GenerateFull();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, CallInEditor, Category="GenerateInterface")
	void UnGenerateFull();
};
