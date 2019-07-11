// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BATestGameMode.h"
#include "BATestHUD.h"
#include "BAGameState.h"
#include "BATestCharacter.h"
#include "BAPlayerController.h"
#include "BattleAreaModeComponent.h"

#include "UObject/ConstructorHelpers.h"


ABATestGameMode::ABATestGameMode()
	: Super()
{
    PrimaryActorTick.bCanEverTick = true;
    bAllowTickBeforeBeginPlay = false;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

    PlayerControllerClass = ABAPlayerController::StaticClass();

	// use our custom HUD class
	HUDClass = ABATestHUD::StaticClass();

    GameStateClass = ABAGameState::StaticClass();

    BattleAreaComponent = CreateDefaultSubobject<UBattleAreaModeComponent>(TEXT("BattleAreaComponent"));
}

void ABATestGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

}
