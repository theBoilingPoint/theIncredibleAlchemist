// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class ALCHEMIST_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Mix two colors using realistic paint mixing
	UFUNCTION(BlueprintCallable, Category = "Color Mixing")
	static FLinearColor MixColors(FLinearColor Color1, FLinearColor Color2, float MixAmount);
};