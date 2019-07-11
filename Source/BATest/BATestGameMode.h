// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "BATestGameMode.generated.h"


UCLASS(minimalapi)
class ABATestGameMode : public AGameModeBase
{
    GENERATED_BODY()


    UPROPERTY(VisibleDefaultsOnly)
    class UBattleAreaModeComponent* BattleAreaComponent;

public:
	ABATestGameMode();

    virtual void PostLogin(APlayerController* NewPlayer) override;

    FORCEINLINE UBattleAreaModeComponent* GetBattleAreaComponent() const { return BattleAreaComponent; }
};
