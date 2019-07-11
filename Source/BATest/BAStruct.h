// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector2D.h"

#include "BAStruct.generated.h"


UENUM(BlueprintType)
enum class EBattleAreaState : uint8
{
    Initial,
    Waiting,
    Shrinking
};

USTRUCT(BlueprintType)
struct FBattleAreaStage
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float Radius;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float ShrinkTime;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float WaitTime;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FVector2D Center;

    FBattleAreaStage()
    {
        Radius = 10000.0f;
        WaitTime = 5.0f;
        ShrinkTime = 10.f;
    }

};
