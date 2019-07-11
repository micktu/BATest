// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BAStruct.h"

#include "BattleAreaModeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATEST_API UBattleAreaModeComponent : public UActorComponent
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = BattleArea)
    TArray<FBattleAreaStage> Stages;

public:	
	UBattleAreaModeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    FORCEINLINE int NumStages() const { return Stages.Num(); }

    FORCEINLINE FBattleAreaStage GetStage(int index) { return Stages[index]; }
		
};
