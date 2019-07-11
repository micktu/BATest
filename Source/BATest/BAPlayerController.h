// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "BAStruct.h"

#include "BAPlayerController.generated.h"


UCLASS()
class BATEST_API ABAPlayerController : public APlayerController
{
    GENERATED_BODY()

    UPROPERTY()
    bool bWasOutside;

    UFUNCTION(Client, Reliable)
    void ClientNotifyBattleAreaHazard(bool bIsOutside);

public:
    UFUNCTION(BlueprintImplementableEvent)
    void OnBattleAreaStateChanged(EBattleAreaState newState, int stageNumber, float statePeriod);

    UFUNCTION(BlueprintImplementableEvent)
    void OnBattleAreaHazard(bool bIsInDanger);


    UFUNCTION()
    void CheckNotifyBattleAreaHazard(bool bIsOutside);

};
