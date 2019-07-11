// Fill out your copyright notice in the Description page of Project Settings.


#include "BAPlayerController.h"


void ABAPlayerController::ClientNotifyBattleAreaHazard_Implementation(bool bIsOutside)
{
        OnBattleAreaHazard(bIsOutside);
}

void ABAPlayerController::CheckNotifyBattleAreaHazard(bool bIsOutside)
{
    // Avoid extra RPCs by checking if the value has changed.
    if (bWasOutside != bIsOutside)
    {
        ClientNotifyBattleAreaHazard(bIsOutside);
    }

    bWasOutside = bIsOutside;
}
