// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleArea.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"


const float ABattleArea::SCALE_RATIO = 50.0f;

// Sets default values
ABattleArea::ABattleArea()
{
	PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Root);
    Mesh->bCastDynamicShadow = false;
    Mesh->CastShadow = false;
    Mesh->SetCollisionProfileName("NoCollision");
    Mesh->SetRelativeScale3D(FVector(100.0f, 100.0f, 100.0f));
}

// Called when the game starts or when spawned
void ABattleArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleArea::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABattleArea::SetRadius(float newRadius)
{
    FVector scale = Mesh->GetComponentScale();
    scale.X = newRadius / SCALE_RATIO;
    scale.Y = newRadius / SCALE_RATIO;
    Mesh->SetWorldScale3D(scale);
}
