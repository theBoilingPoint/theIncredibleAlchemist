// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
#include "mixbox.h"

FLinearColor UMyBlueprintFunctionLibrary::MixColors(FLinearColor Color1, FLinearColor Color2, float MixAmount)
{
    // Clamp MixAmount between 0 and 1
    MixAmount = FMath::Clamp(MixAmount, 0.0f, 1.0f);

    // Mixbox expects values in 0-1 range (which FLinearColor already is)
    float outR, outG, outB;

    // Use linear float version since Unreal uses linear color space
    mixbox_lerp_linear_float(
        Color1.R, Color1.G, Color1.B,  // First color
        Color2.R, Color2.G, Color2.B,  // Second color
        MixAmount,                      // Mix ratio (0 = all Color1, 1 = all Color2)
        &outR, &outG, &outB            // Output
    );

    return FLinearColor(outR, outG, outB, 1.0f);
}