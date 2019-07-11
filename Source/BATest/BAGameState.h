// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "BAGameState.generated.h"


UCLASS()
class BATEST_API ABAGameState : public AGameStateBase
{
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly)
    class UBattleAreaStateComponent* BattleAreaComponent;

public:
    ABAGameState();

    virtual void BeginPlay() override;
};
