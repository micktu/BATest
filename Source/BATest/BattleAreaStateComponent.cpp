// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleAreaStateComponent.h"
#include "BattleAreaModeComponent.h"
#include "BATestCharacter.h"
#include "BAGameState.h"
#include "BATestGameMode.h"
#include "BAPlayerController.h"

#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"


UBattleAreaStateComponent::UBattleAreaStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBattleAreaStateComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    DOREPLIFETIME(UBattleAreaStateComponent, CurrentState);
    DOREPLIFETIME(UBattleAreaStateComponent, CurrentStage);
    DOREPLIFETIME(UBattleAreaStateComponent, OldStage);
    DOREPLIFETIME(UBattleAreaStateComponent, NewStage);
    // Useful for clients that joined late
    DOREPLIFETIME_CONDITION(UBattleAreaStateComponent, StateTime, COND_InitialOnly);
}

void UBattleAreaStateComponent::BeginPlay()
{
    Super::BeginPlay();

    // Server doesn't actually need it atm.
    BattleAreaActor = GetWorld()->SpawnActor<ABattleArea>(BattleAreaClass, FVector::ZeroVector, FRotator::ZeroRotator);
}

void UBattleAreaStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    bool bIsServer = ENetRole::ROLE_Authority == GetOwnerRole();

    switch (CurrentState)
    {
    case EBattleAreaState::Initial:
        if (bIsServer && 0 == CurrentStage)
        {
            UWorld* world = GetWorld();
            // FIXME This should be a separate init proc.
            GameModeComponent = world->GetAuthGameMode<ABATestGameMode>()->GetBattleAreaComponent();
            world->GetTimerManager().SetTimer(HealthCheckTimer, this, &UBattleAreaStateComponent::CheckPlayerHazard, 1.0f, true, 1.0f);
            OldStage = GameModeComponent->GetStage(CurrentStage);
            NewStage = GameModeComponent->GetStage(++CurrentStage);
            NewStage.Center = GetNewCenter();
            SetState(EBattleAreaState::Waiting);
        }
        break;
    case EBattleAreaState::Waiting:
        if (bIsServer && StateTime >= OldStage.WaitTime)
        {
            SetState(EBattleAreaState::Shrinking);
        }
        break;
    case EBattleAreaState::Shrinking:
        if (StateTime < NewStage.ShrinkTime)
        {
            float progress = FMath::Clamp(StateTime / OldStage.ShrinkTime, 0.0f, 1.0f);
            UpdateBattleArea(progress);
        }
        else if (bIsServer)
        {  
            OldStage = NewStage;
            if (++CurrentStage < GameModeComponent->NumStages())
            {
                NewStage = GameModeComponent->GetStage(CurrentStage);
                NewStage.Center = GetNewCenter();
                SetState(EBattleAreaState::Waiting);
            }
            else
            {
                SetState(EBattleAreaState::Initial);
            }

        }
        break;
    default:
        break;
    }

    StateTime += DeltaTime;
}

void UBattleAreaStateComponent::OnRep_CurrentState()
{
    // SetState is only called on server, and this notification is how it's called on the client.
    SetState(CurrentState);
}

void UBattleAreaStateComponent::UpdateBattleArea(float progress)
{
    if (!IsValid(BattleAreaActor)) return;
    
    float newRadius = FMath::Lerp(OldStage.Radius, NewStage.Radius, progress);
    BattleAreaActor->SetRadius(newRadius);

    FVector2D newCenter = FMath::Lerp(OldStage.Center, NewStage.Center, progress);
    BattleAreaActor->SetCenter(newCenter);
}

void UBattleAreaStateComponent::SetState(EBattleAreaState newState)
{
    CurrentState = newState;
    StateTime = 0.0f;
    UpdateBattleArea(0.0f);

    float period = EBattleAreaState::Waiting == CurrentState ? OldStage.WaitTime : OldStage.ShrinkTime;
    ABAPlayerController* player = Cast<ABAPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

    if (IsValid(player)) // Otherwise crashes the dedicated server.
    {
        player->OnBattleAreaStateChanged(CurrentState, CurrentStage, period);
    }
}

void UBattleAreaStateComponent::CheckPlayerHazard()
{
    float circleRadius = GetCurrentRadius();
    FVector circleLocation = GetCurrentCenter();

    for (auto iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
    {
        auto player = Cast<ABAPlayerController>(*iter);

        auto character = Cast<ABATestCharacter>(player->GetPawn());
        float characterRadius = character->GetCapsuleComponent()->GetScaledCapsuleRadius();
        FVector characterLocation = character->GetActorLocation();

        float radius = circleRadius - characterRadius;
        bool bIsOutside = FVector::DistSquared2D(characterLocation, circleLocation) > radius * radius;

        player->CheckNotifyBattleAreaHazard(bIsOutside);
    }
}
