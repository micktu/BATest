// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BattleArea.h"
#include "BAStruct.h"

#include "BattleAreaStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATEST_API UBattleAreaStateComponent : public UActorComponent
{
	GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = BattleArea)
    TSubclassOf<class ABattleArea> BattleAreaClass;

    UPROPERTY()
    class UBattleAreaModeComponent* GameModeComponent;

    UPROPERTY()
    ABattleArea* BattleAreaActor;

    UPROPERTY(ReplicatedUsing=OnRep_CurrentState)
    EBattleAreaState CurrentState;

    UPROPERTY(Replicated)
    int CurrentStage;

    UPROPERTY(Replicated)
    FBattleAreaStage OldStage;
    
    UPROPERTY(Replicated)
    FBattleAreaStage NewStage;

    UPROPERTY(Replicated)
    float StateTime;

    UPROPERTY()
    FTimerHandle HealthCheckTimer;

public:	
	UBattleAreaStateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION()
    void OnRep_CurrentState();

    void UpdateBattleArea(float progress);

    void SetState(EBattleAreaState newState);

    void CheckPlayerHazard();

    FORCEINLINE float GetCurrentRadius() const
    {
        return BattleAreaActor->GetRadius();
    }

    FORCEINLINE FVector GetCurrentCenter() const { return BattleAreaActor->GetCenter(); }
};
