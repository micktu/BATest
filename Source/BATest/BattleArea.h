// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BAStruct.h"

#include "BattleArea.generated.h"


UCLASS()
class BATEST_API ABattleArea : public AActor
{
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly)
    class USceneComponent* Root;

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class UStaticMeshComponent* Mesh;

public:
    static const float SCALE_RATIO;

	ABattleArea();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
    
    FORCEINLINE float GetRadius() const { return Mesh->GetComponentScale().X * SCALE_RATIO; }
    
    FORCEINLINE void SetRadius(float newRadius);

    FORCEINLINE FVector GetCenter() const { return Mesh->GetComponentLocation(); }
    
    FORCEINLINE void SetCenter(FVector2D newCenter) { Mesh->SetWorldLocation(FVector(newCenter, 0.0f)); }

    FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

};
