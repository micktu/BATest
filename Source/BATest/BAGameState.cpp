// Fill out your copyright notice in the Description page of Project Settings.


#include "BAGameState.h"
#include "BattleAreaStateComponent.h"


ABAGameState::ABAGameState()
    : Super()
{
    BattleAreaComponent = CreateDefaultSubobject<UBattleAreaStateComponent>(TEXT("BattleAreaComponent"));
    BattleAreaComponent->SetIsReplicated(true);
}

void ABAGameState::BeginPlay()
{
    Super::BeginPlay();
}
