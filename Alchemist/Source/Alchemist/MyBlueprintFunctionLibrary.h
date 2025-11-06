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

    // Convert RGB to Latent space (call once when starting or adding new color)
    UFUNCTION(BlueprintCallable, Category = "Color Mixing")
    static TArray<float> RGBToLatent(FLinearColor Color);

    // Mix current latent with new color (stores result in latent space)
    UFUNCTION(BlueprintCallable, Category = "Color Mixing")
    static TArray<float> MixLatentWithColor(const TArray<float>& CurrentLatent, FLinearColor NewColor, float MixAmount);

    // Convert Latent back to RGB for display
    UFUNCTION(BlueprintCallable, Category = "Color Mixing")
    static FLinearColor LatentToRGB(const TArray<float>& Latent);
};