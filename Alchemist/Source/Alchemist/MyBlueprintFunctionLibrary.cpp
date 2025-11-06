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

TArray<float> UMyBlueprintFunctionLibrary::RGBToLatent(FLinearColor Color)
{
    mixbox_latent latent;

    // Convert RGB to latent space
    mixbox_linear_float_rgb_to_latent(Color.R, Color.G, Color.B, latent);

    // Convert to TArray for Blueprint
    TArray<float> result;
    result.SetNum(MIXBOX_LATENT_SIZE);
    for (int32 i = 0; i < MIXBOX_LATENT_SIZE; i++)
    {
        result[i] = latent[i];
    }

    return result;
}

TArray<float> UMyBlueprintFunctionLibrary::MixLatentWithColor(const TArray<float>& CurrentLatent, FLinearColor NewColor, float MixAmount)
{
    // Clamp mix amount
    MixAmount = FMath::Clamp(MixAmount, 0.0f, 1.0f);

    // Convert new color to latent
    mixbox_latent newLatent;
    mixbox_linear_float_rgb_to_latent(NewColor.R, NewColor.G, NewColor.B, newLatent);

    // Mix in latent space
    TArray<float> result;
    result.SetNum(MIXBOX_LATENT_SIZE);

    for (int32 i = 0; i < MIXBOX_LATENT_SIZE; i++)
    {
        // Lerp: (1-t)*current + t*new
        float currentVal = (CurrentLatent.IsValidIndex(i)) ? CurrentLatent[i] : 0.0f;
        result[i] = (1.0f - MixAmount) * currentVal + MixAmount * newLatent[i];
    }

    return result;
}

FLinearColor UMyBlueprintFunctionLibrary::LatentToRGB(const TArray<float>& Latent)
{
    // Copy TArray to mixbox_latent
    mixbox_latent latent;
    for (int32 i = 0; i < MIXBOX_LATENT_SIZE; i++)
    {
        latent[i] = (Latent.IsValidIndex(i)) ? Latent[i] : 0.0f;
    }

    // Convert to RGB
    float r, g, b;
    mixbox_latent_to_linear_float_rgb(latent, &r, &g, &b);

    return FLinearColor(r, g, b, 1.0f);
}